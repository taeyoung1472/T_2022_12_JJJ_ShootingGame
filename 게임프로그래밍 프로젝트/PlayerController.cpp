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

PlayerController::PlayerController() : m_speeed(250), m_timer(0)
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::Awake()
{
	shared_ptr<Sprite> runSprite = ResourceManager::GetInst()->Load<Sprite>(L"PlayerRunSprite", L"Sprite\\PlayerRun.bmp");
	runSprite->SetPixelPerfect(16);
	runSprite->SetRow(4);
	m_runSprite = runSprite;

	shared_ptr<Sprite> idleSprite = ResourceManager::GetInst()->Load<Sprite>(L"PlayerIdleSprite", L"Sprite\\PlayerIdle.bmp");
	idleSprite->SetPixelPerfect(16);
	idleSprite->SetRow(4);
	m_idleSprite = idleSprite;
}

void PlayerController::Update()
{
	Vector2 input;

	if (Input->GetKey(KeyCode::A)) input.x -= 1;
	if (Input->GetKey(KeyCode::D)) input.x += 1;
	if (Input->GetKey(KeyCode::W)) input.y -= 1;
	if (Input->GetKey(KeyCode::S)) input.y += 1;

	input = Normalize(input);

	if (input.x == 0 && input.y == 0 && m_isRunning) 
	{
		m_isRunning = false;
		m_curRenderingSprite = m_idleSprite;
		m_animationTimer = 0.2f;
		m_timer = 0.0f;
		GetGameObject()->GetComponent<SpriteRendere>(COMPONENT_TYPE::SPRITERENDERE)->SetSprite(m_curRenderingSprite);
	}
	else if((input.x != 0 || input.y != 0) && !m_isRunning)
	{
		m_isRunning = true;
		m_curRenderingSprite = m_runSprite;
		m_animationTimer = 0.1f;
		m_timer = 0.0f;
		GetGameObject()->GetComponent<SpriteRendere>(COMPONENT_TYPE::SPRITERENDERE)->SetSprite(m_curRenderingSprite);
	}

	GetTransform()->Translate(input * m_speeed * Time->GetDeltaTime());

	m_timer += Time->GetDeltaTime();
	if (m_timer > m_animationTimer) {
		int curRow = m_curRenderingSprite->GetCurRow();
		m_curRenderingSprite->SetCurRow((curRow + 1) % m_curRenderingSprite->GetRow());
		m_timer = 0;
	}

	Vector2 worldPos = GetTransform()->GetWorldPosition();
}
