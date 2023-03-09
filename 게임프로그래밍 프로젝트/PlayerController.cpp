#include "pch.h"
#include "PlayerController.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Transform.h"
#include "GameObject.h"
#include "SpriteRendere.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "Math.h"
#include "GameLogic.h"
#include "Slider.h"
#include "SoundManager.h"
#include "Random.h"
#include "Collider.h";
#include "Scene.h"
#include "SceneManager.h"
#include "Math.h"
#include "Gun.h"

PlayerController::PlayerController() : m_speed(250), m_timer(0), m_stepTimer(0), m_stepDelay(0.15f)
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::Awake()
{
	SoundManager::GetInst()->LoadSound(L"Step1", false, L"Audio\\step1.wav");
	SoundManager::GetInst()->LoadSound(L"Step2", false, L"Audio\\step2.wav");

	shared_ptr<Sprite> runSprite = ResourceManager::GetInst()->Load<Sprite>(L"PlayerRunSprite", L"Sprite\\PlayerRun.bmp");
	runSprite->SetRow(4);
	runSprite->SetColumn(2);
	m_runSprite = runSprite;

	shared_ptr<Sprite> idleSprite = ResourceManager::GetInst()->Load<Sprite>(L"PlayerIdleSprite", L"Sprite\\PlayerIdle.bmp");
	idleSprite->SetRow(4);
	idleSprite->SetColumn(2);
	m_idleSprite = idleSprite;

	SoundManager::GetInst()->LoadSound(L"HpItem", false, L"Audio\\HpItemUse.wav");
}

void PlayerController::Update()
{
	Vector2 input;
	float rot = 0;

	if (Input->GetKey(KeyCode::A)) input.x -= 1;
	if (Input->GetKey(KeyCode::D)) input.x += 1;
	if (Input->GetKey(KeyCode::W)) input.y -= 1;
	if (Input->GetKey(KeyCode::S)) input.y += 1;

	if (Input->GetKey(KeyCode::RIGHT)) rot += 60;

	input = Normalize(input);

	if (input.x == 0 && input.y == 0 && m_isRunning) 
	{
		m_isRunning = false;
		m_curRenderingSprite = m_idleSprite;
		m_animationTimer = 0.2f;
		m_timer = 0.0f;
		GetGameObject()->GetComponent<SpriteRendere>()->SetSprite(m_curRenderingSprite);
	}
	else if((input.x != 0 || input.y != 0) && !m_isRunning)
	{
		m_isRunning = true;
		m_curRenderingSprite = m_runSprite;
		m_animationTimer = 0.1f;
		m_timer = 0.0f;
		GetGameObject()->GetComponent<SpriteRendere>()->SetSprite(m_curRenderingSprite);
	}

	if (m_isRunning) 
	{
		m_stepTimer += Time->GetDeltaTime();
	}

	GetTransform()->Translate(input * m_speed * Time->GetDeltaTime());
	GetTransform()->Rotate(rot * Time->GetDeltaTime());

	m_timer += Time->GetDeltaTime();
	if (m_timer > m_animationTimer) {
		m_timer = 0;
		GetGameObject()->GetComponent<SpriteRendere>()->MoveRow(1);
	}
	if (m_stepTimer > m_stepDelay) 
	{
		m_stepTimer = 0;
		Random rand;
		m_stepDelay = 0.2f + (0.01f * rand.Range(0, 5));

		if (m_stepIndex == 0) {
			SoundManager::GetInst()->Play(L"Step1");
		}
		else {
			SoundManager::GetInst()->Play(L"Step2");
		}

		m_stepIndex = (m_stepIndex + 1) % 2;
	}

	// ¿À¸¥ÂÊ
	if (GetTransform()->GetWorldPosition().x < Input->GetMousePos().x && !m_isRight) 
	{
		GetGameObject()->GetComponent<SpriteRendere>()->SetColumn(0);
		m_gun->GetGameObject()->GetComponent<SpriteRendere>()->SetColumn(0);
		m_gun->GetGameObject()->GetTransform()->SetLocalPosition(m_gunOriginPos);
		m_gun->GetGameObject()->GetComponent<Gun>()->SetOriginPosAndKnockBackPosAndFirePos(m_gunOriginPos, Vector2(m_gunOriginPos.x - 20, m_gunOriginPos.y), Vector2(40, -10));
		
		m_LHand->SetLocalPosition(m_LhandOriginPos);
		m_RHand->SetLocalPosition(m_RhandOriginPos);
		
		m_isRight = true;
	}
	// ¿ÞÂÊ
	else if(GetTransform()->GetWorldPosition().x > Input->GetMousePos().x && m_isRight)
	{
		GetGameObject()->GetComponent<SpriteRendere>()->SetColumn(1);
		m_gun->GetGameObject()->GetComponent<SpriteRendere>()->SetColumn(1);
		m_gun->GetGameObject()->GetTransform()->SetLocalPosition(Vector2(m_gunOriginPos.x - 150, m_gunOriginPos.y));
		m_gun->GetGameObject()->GetComponent<Gun>()->SetOriginPosAndKnockBackPosAndFirePos(Vector2(m_gunOriginPos.x - 150, m_gunOriginPos.y), Vector2(m_gunOriginPos.x - 130, m_gunOriginPos.y), Vector2(-40, -10));
		
		m_LHand->SetLocalPosition(m_LhandOriginPos - Vector2(-20, 0));
		m_RHand->SetLocalPosition(m_RhandOriginPos - Vector2(-100, 0));
		
		m_isRight = false;
	}
}

void PlayerController::CollisionEnter(weak_ptr<Collider> collision)
{
	if (collision.lock()->GetGameObject()->GetTag() == L"Enemy") 
	{
		Damaged(1);
		CurScene->Destroy(collision.lock()->GetGameObject());
		SoundManager::GetInst()->Play(L"EnemyAttack");
	}
}

void PlayerController::SetHpSlider(shared_ptr<Slider> slider)
{
	m_hp = m_maxHp;
	m_hpSlider = slider;
	m_hpSlider->Init(m_maxHp);
}

void PlayerController::SetGun(shared_ptr<Gun> gun)
{
	m_gun = gun;
	m_gunOriginPos = m_gun->GetTransform()->GetLocalPosition();
}

void PlayerController::SetHand(shared_ptr<Transform> LHand, shared_ptr<Transform> RHand)
{
	m_LHand = LHand;
	m_RHand = RHand;

	m_RhandOriginPos = m_RHand->GetLocalPosition();
	m_LhandOriginPos = m_LHand->GetLocalPosition();
}

void PlayerController::Damaged(int dmg)
{
	m_hp -= dmg;
	m_hp = Clamp(m_hp, 0, m_maxHp);
	m_hpSlider->SetValue(m_hp);

	if (m_hp == 0) 
	{
		SendMessage(GameLogic::GetInst()->GetWndHandle(), WM_CLOSE, 0, 0);
	}
}

void PlayerController::GetItem(ITEM_TYPE type)
{
	SoundManager::GetInst()->Play(L"HpItem");
	if (type == ITEM_TYPE::HP) {
		Damaged(-1);
	}
	if (type == ITEM_TYPE::SPEED) {
		m_speed += 25;
		Damaged(-1);
	}
	if (type == ITEM_TYPE::FIRE_RATE) {
		m_gun->FireRateUpgrade();
	}
}
