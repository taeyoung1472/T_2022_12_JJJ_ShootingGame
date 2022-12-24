#include "pch.h"
#include "GameLogic.h"
#include "Scene.h"

// Manager
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "PathManager.h"
#include "PhysicsManager.h"
#include "SoundManager.h"
#include "EnemySpawnManager.h"

// Object
#include "GameObject.h"
#include "Component.h"
#include "SpriteRendere.h"
#include "Collider.h";
#include "Slider.h"

// Script
#include "PlayerController.h"
#include "Gun.h"
#include "Random.h"

GameLogic::GameLogic()
	: m_Resolution{}
	, m_memHdc(0)
	, m_offHdc(0)
	, m_offBit(0)
{
}

GameLogic::~GameLogic()
{
	ReleaseDC(m_hWnd, m_memHdc);
}

int GameLogic::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_Resolution = _ptResolution;

	m_memHdc = GetDC(m_hWnd);

	m_offHdc = CreateCompatibleDC(m_memHdc);
	m_offBit = CreateCompatibleBitmap(m_memHdc, m_Resolution.x, m_Resolution.y);
	
	SelectObject(m_offHdc, m_offBit);

	// TODO : �ʱ�ȭ ����
	Time->Init();
	Input->Init(m_hWnd);
	PathManager::GetInst()->Init();
	SoundManager::GetInst()->Init();
	SoundManager::GetInst()->LoadSound(L"BGM", true, L"Audio\\BGM.wav");
	SoundManager::GetInst()->Play(L"BGM");
	EnemySpawnManager::GetInst()->Init();

	// TODO : Scene ����
	shared_ptr<Scene> sampleScene = make_shared<Scene>();

	// TODO : ���� �غ� ����

#pragma region GameObject
#pragma region Background
	{
		Vector2 resolution = GetResolution();

		shared_ptr<GameObject> background = GameObject::Instantiate(Vector2(resolution.x / 2, resolution.y / 2));

		shared_ptr<Sprite> backgroundSprit = ResourceManager::GetInst()->Load<Sprite>(L"backgroundSprite", L"Sprite\\background.bmp");
		backgroundSprit->SetPixelPerfect(25);

		background->AddComponent<SpriteRendere>(make_shared<SpriteRendere>());
		background->GetComponent<SpriteRendere>()->SetSprite(backgroundSprit);

		sampleScene->AddGameObject(background);
	}
#pragma endregion

#pragma region Player
	shared_ptr<GameObject> player = GameObject::Instantiate();
	player->AddComponent<PlayerController>(make_shared<PlayerController>());

	player->AddComponent<SpriteRendere>(make_shared<SpriteRendere>());
	shared_ptr<Sprite> playerSprite = ResourceManager::GetInst()->Load<Sprite>(L"PlayerSprite", L"Sprite\\PlayerIdle.bmp");
	playerSprite->SetPixelPerfect(16);
	playerSprite->SetRow(4);

	player->AddComponent<Collider>(make_shared<Collider>());
	player->GetComponent<Collider>()->SetSize(Vector2(75, 75));
	player->GetComponent<Collider>()->SetCenter(Vector2(0, 35));

	player->GetComponent<SpriteRendere>()->SetSprite(playerSprite);

	player->SetTag(L"Player");

	sampleScene->AddGameObject(player);
#pragma endregion

#pragma region Gun
	shared_ptr<GameObject> gun = GameObject::Instantiate(Vector2(75, 52), player->GetTransform());
	gun->AddComponent<SpriteRendere>(make_shared<SpriteRendere>());
	gun->AddComponent<Gun>(make_shared<Gun>());

	sampleScene->AddGameObject(gun);
#pragma endregion

#pragma region Hand
	{
		shared_ptr<Sprite> handSprite = ResourceManager::GetInst()->Load<Sprite>(L"Hand", L"Sprite\\Hand.bmp");

		handSprite->SetPixelPerfect(80);

		shared_ptr<GameObject> FrontHand = GameObject::Instantiate(Vector2(-10, -2), gun->GetTransform());
		FrontHand->AddComponent<SpriteRendere>(make_shared<SpriteRendere>());
		FrontHand->GetComponent<SpriteRendere>()->SetSprite(handSprite);

		sampleScene->AddGameObject(FrontHand);

		shared_ptr<GameObject> BehindHand = GameObject::Instantiate(Vector2(-50, 10), gun->GetTransform());
		BehindHand->AddComponent<SpriteRendere>(make_shared<SpriteRendere>());
		BehindHand->GetComponent<SpriteRendere>()->SetSprite(handSprite);

		sampleScene->AddGameObject(BehindHand);
	}
#pragma endregion

#pragma region Border
	{
		Vector2 resolution = GetResolution();
		float borderSpace = 100;

		// Right
		{
			shared_ptr<GameObject> border = GameObject::Instantiate(Vector2(-borderSpace / 2, resolution.y / 2));

			border->AddComponent<Collider>(make_shared<Collider>());
			border->GetComponent<Collider>()->SetSize(Vector2(borderSpace, resolution.y));

			sampleScene->AddGameObject(border);
		}
		// Left
		{
			shared_ptr<GameObject> border = GameObject::Instantiate(Vector2(resolution.x + borderSpace / 2, resolution.y / 2));

			border->AddComponent<Collider>(make_shared<Collider>());
			border->GetComponent<Collider>()->SetSize(Vector2(borderSpace, resolution.y));

			sampleScene->AddGameObject(border);
		}
		// Up
		{
			shared_ptr<GameObject> border = GameObject::Instantiate(Vector2(resolution.x / 2, -borderSpace / 2));

			border->AddComponent<Collider>(make_shared<Collider>());
			border->GetComponent<Collider>()->SetSize(Vector2(resolution.x, borderSpace));

			sampleScene->AddGameObject(border);
		}
		// Right
		{
			shared_ptr<GameObject> border = GameObject::Instantiate(Vector2(resolution.x / 2, resolution.y + borderSpace / 2));

			border->AddComponent<Collider>(make_shared<Collider>());
			border->GetComponent<Collider>()->SetSize(Vector2(resolution.x, borderSpace));

			sampleScene->AddGameObject(border);
		}
	}
#pragma endregion
#pragma endregion

#pragma region UI/UX

#pragma region HpSlider

	{
		Vector2 displayPos = Vector2(425, 675);

		shared_ptr<GameObject> hpSliderBackground = GameObject::Instantiate(displayPos);
		hpSliderBackground->AddComponent<SpriteRendere>(make_shared<SpriteRendere>());
		shared_ptr<Sprite> sliderBackgroundSprite = ResourceManager::GetInst()->Load<Sprite>(L"hpSliderBackground", L"Sprite\\hpSliderBackground.bmp");
		sliderBackgroundSprite->SetPixelPerfect(16);
		hpSliderBackground->GetComponent<SpriteRendere>()->SetSprite(sliderBackgroundSprite);
		sampleScene->AddGameObject(hpSliderBackground);


		shared_ptr<GameObject> hpSliderFill = GameObject::Instantiate(displayPos);
		hpSliderFill->AddComponent<Slider>(make_shared<Slider>());
		shared_ptr<Sprite> sliderFillSprite = ResourceManager::GetInst()->Load<Sprite>(L"hpSliderFill", L"Sprite\\hpSliderFill.bmp");
		sliderFillSprite->SetPixelPerfect(16);
		hpSliderFill->GetComponent<Slider>()->SetSprite(sliderFillSprite);
		sampleScene->AddGameObject(hpSliderFill);

		player->GetComponent<PlayerController>()->SetHpSlider(hpSliderFill->GetComponent<Slider>());
	}

#pragma endregion

#pragma endregion

	EnemySpawnManager::GetInst()->SetTarget(player->GetTransform());

	// TODO : Scene ����ϰ� �ε��� ���� ����
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
	// TODO : Update ����
	PhysicsManager::GetInst()->Update();
	TimeManager::GetInst()->Update();
	Input->Update();
	EnemySpawnManager::GetInst()->Update();
	SoundManager::GetInst()->Update();
	SceneManager::GetInst()->Update();
}

void GameLogic::Render()
{
	PatBlt(m_offHdc, 0, 0, m_Resolution.x, m_Resolution.y, WHITENESS);

	// TODO : Rendering ����
	SceneManager::GetInst()->Render();

	BitBlt(m_memHdc, 0, 0, m_Resolution.x, m_Resolution.y, m_offHdc, 0, 0, SRCCOPY);
}