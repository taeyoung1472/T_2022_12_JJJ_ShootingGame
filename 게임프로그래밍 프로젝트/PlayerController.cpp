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

PlayerController::PlayerController() : m_speeed(250), m_timer(0), m_stepTimer(0), m_stepDelay(0.15f)
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
	runSprite->SetPixelPerfect(16);
	runSprite->SetRow(4);
	m_runSprite = runSprite;

	shared_ptr<Sprite> idleSprite = ResourceManager::GetInst()->Load<Sprite>(L"PlayerIdleSprite", L"Sprite\\PlayerIdle.bmp");
	idleSprite->SetPixelPerfect(16);
	idleSprite->SetRow(4);
	m_idleSprite = idleSprite;

	SoundManager::GetInst()->LoadSound(L"HpItem", false, L"Audio\\HpItemUse.wav");
}

void PlayerController::Update()
{
	Vector2 input;
	float rot = 0;

	if (Input->GetKeyDown(KeyCode::UP)) Damaged(1);

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

	GetTransform()->Translate(input * m_speeed * Time->GetDeltaTime());
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

void PlayerController::Damaged(int dmg)
{
	m_hp -= dmg;
	m_hp = Clamp(m_hp, 0, m_maxHp);
	m_hpSlider->SetValue(m_hp);
}

void PlayerController::GetItem(ITEM_TYPE type)
{
	if (type == ITEM_TYPE::HP) {
		SoundManager::GetInst()->Play(L"HpItem");
		Damaged(-1);
	}
}
