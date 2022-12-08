#include "pch.h"
#include "GameLogic.h"
#include "Scene.h"

// Manager
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "PathManager.h"

// Object
#include "GameObject.h"
#include "Component.h"
#include "SpriteRendere.h"

// Script
#include "PlayerController.h"
#include "Gun.h"

GameLogic::GameLogic()
	: m_Resolution{}
	, m_hDC(0)
	, m_memDC(0)
	, m_hBit(0)
{
}

GameLogic::~GameLogic()
{
	ReleaseDC(m_hWnd, m_hDC);
}

int GameLogic::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_Resolution = _ptResolution;
	m_hDC = GetDC(m_hWnd);

	m_hBit = CreateCompatibleBitmap(m_hDC, m_Resolution.x, m_Resolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);
	SelectObject(m_memDC, m_hBit);

	// TODO : 초기화 과정
	Time->Init();
	Input->Init(m_hWnd);
	PathManager::GetInst()->Init();

	// TODO : Scene 생성
	shared_ptr<Scene> sampleScene = make_shared<Scene>();

	// TODO : 게임 준비 과정
#pragma region Player
	shared_ptr<GameObject> player = make_shared<GameObject>();
	player->AddComponent<Transform>(make_shared<Transform>());
	player->AddComponent<PlayerController>(make_shared<PlayerController>());

	player->AddComponent<SpriteRendere>(make_shared<SpriteRendere>());
	shared_ptr<Sprite> playerSprite = ResourceManager::GetInst()->Load<Sprite>(L"PlayerSprite", L"Sprite\\PlayerIdle.bmp");
	playerSprite->SetPixelPerfect(16);
	playerSprite->SetRow(4);

	player->GetComponent<SpriteRendere>(COMPONENT_TYPE::SPRITERENDERE)->SetSprite(playerSprite);

	sampleScene->AddGameObject(player);
#pragma endregion

#pragma region Gun
	shared_ptr<GameObject> gun = make_shared<GameObject>();
	gun->AddComponent<Transform>(make_shared<Transform>());
	gun->AddComponent<SpriteRendere>(make_shared<SpriteRendere>());
	gun->AddComponent<Gun>(make_shared<Gun>());
	gun->GetComponent<Transform>(COMPONENT_TYPE::TRANSFORM)->SetParent(player->GetComponent<Transform>(COMPONENT_TYPE::TRANSFORM));
	gun->GetComponent<Transform>(COMPONENT_TYPE::TRANSFORM)->SetLocalPosition(Vector2(75, 52));

	sampleScene->AddGameObject(gun);
#pragma endregion

#pragma region Hand
	{
		shared_ptr<Sprite> handSprite = ResourceManager::GetInst()->Load<Sprite>(L"Hand", L"Sprite\\Hand.bmp");

		handSprite->SetPixelPerfect(80);

		shared_ptr<GameObject> FrontHand = make_shared<GameObject>();
		FrontHand->AddComponent<SpriteRendere>(make_shared<SpriteRendere>());
		FrontHand->AddComponent<Transform>(make_shared<Transform>());
		FrontHand->GetComponent<Transform>(COMPONENT_TYPE::TRANSFORM)->SetParent(gun->GetComponent<Transform>(COMPONENT_TYPE::TRANSFORM));
		FrontHand->GetComponent<Transform>(COMPONENT_TYPE::TRANSFORM)->SetLocalPosition(Vector2(-10, -2));
		FrontHand->GetComponent<SpriteRendere>(COMPONENT_TYPE::SPRITERENDERE)->SetSprite(handSprite);

		sampleScene->AddGameObject(FrontHand);

		shared_ptr<GameObject> BehindHand = make_shared<GameObject>();
		BehindHand->AddComponent<SpriteRendere>(make_shared<SpriteRendere>());
		BehindHand->AddComponent<Transform>(make_shared<Transform>());
		BehindHand->GetComponent<Transform>(COMPONENT_TYPE::TRANSFORM)->SetParent(gun->GetComponent<Transform>(COMPONENT_TYPE::TRANSFORM));
		BehindHand->GetComponent<Transform>(COMPONENT_TYPE::TRANSFORM)->SetLocalPosition(Vector2(-50, 10));
		BehindHand->GetComponent<SpriteRendere>(COMPONENT_TYPE::SPRITERENDERE)->SetSprite(handSprite);

		sampleScene->AddGameObject(BehindHand);
	}
#pragma endregion


	// TODO : Scene 등록하고 로드후 게임 시작
	SceneManager::GetInst()->RegisterScene(L"SampleScene", sampleScene);
	SceneManager::GetInst()->LoadScene(L"SampleScene");

	RECT rt = { 0, 0, m_Resolution.x, m_Resolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hWnd, nullptr, 100, 100,
		rt.right - rt.left, rt.bottom - rt.top, 0);

	return S_OK;
}	

void GameLogic::Progress()
{
	Update();
	Render();
}

void GameLogic::Update()
{
	// TODO : Update 과정
	TimeManager::GetInst()->Update();
	Input->Update();
	SceneManager::GetInst()->Update();
}

void GameLogic::Render()
{
	PatBlt(m_memDC, 0, 0, m_Resolution.x, m_Resolution.y, WHITENESS);

	// TODO : Rendering 과정
	SceneManager::GetInst()->Render();

	BitBlt(m_hDC, 0, 0, m_Resolution.x, m_Resolution.y, m_memDC, 0, 0, SRCCOPY);
}