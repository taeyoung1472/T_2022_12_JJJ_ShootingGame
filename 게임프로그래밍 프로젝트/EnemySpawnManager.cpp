#include "pch.h"
#include "EnemySpawnManager.h"
#include "EnemyController.h"
#include "TimeManager.h"
#include "GameObject.h"
#include "Component.h"
#include "SpriteRendere.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Transform.h"
#include "Vector2.h"
#include "GameLogic.h"
#include "Random.h"
#include "Collider.h"
#include "SoundManager.h"
#include "Slider.h"
#include "Math.h"

EnemySpawnManager::EnemySpawnManager()
{

}

EnemySpawnManager::~EnemySpawnManager()
{

}

void EnemySpawnManager::Init()
{
	SoundManager::GetInst()->LoadSound(L"EnemyAttack", false, L"Audio\\EnemyAttack.wav");
	SoundManager::GetInst()->LoadSound(L"EnemyHit", false, L"Audio\\EnemyHit.wav");
	SoundManager::GetInst()->LoadSound(L"EnemyDie", false, L"Audio\\EnemyDie.wav");
}

void EnemySpawnManager::Update()
{
	m_timer += Time->GetDeltaTime();
	if (m_timer >= SPAWN_COOL)
	{
		SPAWN_COOL = Clamp(SPAWN_COOL - m_spawnCoolChangeValue, 1, 5);
		m_timer = 0;

		if (SPAWN_COOL <= 1.1f) 
		{
			m_spawnCoolChangeValue += 0.2f;
			m_spawnPerEnemy++;
			SPAWN_COOL = 5.0f;
		}

		for (int i = 0; i < m_spawnPerEnemy; i++)
		{
			SpawnEnmey();
		}
	}
}

void EnemySpawnManager::SpawnEnmey()
{
	shared_ptr<GameObject> enemy = GameObject::Instantiate();
	enemy->AddComponent<Transform>();
	Vector2 pos;
	Vector2 screen = GameLogic::GetInst()->GetResolution();

	Random rand;

	if (rand.Range(0, 1))
	{
		if (rand.Range(0, 1))
			pos.y = 0;
		else
			pos.y = screen.y;
		pos.x = rand.Range(0.0f, screen.x);
	}
	else
	{
		if (rand.Range(0, 1))
			pos.x = 0;
		else
			pos.x = screen.x;
		pos.y = rand.Range(0.0f, screen.y);
	}
	enemy->GetTransform()->SetWorldPosition(pos);

	enemy->AddComponent<EnemyController>();
	enemy->GetComponent<EnemyController>()->SetTarget(m_target);

	enemy->AddComponent<SpriteRendere>();
	shared_ptr<Sprite> enemySprite = ResourceManager::GetInst()->Load<Sprite>(L"EnemySprite", L"Sprite\\EnemyRun.bmp");
	enemySprite->SetRow(4);
	enemy->GetComponent<SpriteRendere>()->SetSprite(enemySprite);
	enemy->GetComponent<SpriteRendere>()->SetPixelPerfect(16);

	enemy->AddComponent<Collider>();
	enemy->GetComponent<Collider>()->SetSize(Vector2(75, 120));

#pragma region Slider
	shared_ptr<GameObject> hpSliderFill = GameObject::Instantiate(Vector2(0, 85), enemy->GetTransform());
	shared_ptr<GameObject> hpSliderBackground = GameObject::Instantiate(Vector2(0, 85), enemy->GetTransform());

	hpSliderFill->AddComponent<Slider>();
	hpSliderBackground->AddComponent<SpriteRendere>();

	shared_ptr<Sprite> hpSliderBackgroundSprite = ResourceManager::GetInst()->Load<Sprite>(L"hpSliderBackground", L"Sprite\\hpSliderBackground.bmp");
	shared_ptr<Sprite> hpSliderFillSprite = ResourceManager::GetInst()->Load<Sprite>(L"hpSliderFill", L"Sprite\\hpSliderFill.bmp");

	hpSliderBackground->GetComponent<SpriteRendere>()->SetPixelPerfect(75);
	hpSliderFill->GetComponent<Slider>()->SetPixelPerfect(75);

	hpSliderBackground->GetComponent<SpriteRendere>()->SetSprite(hpSliderBackgroundSprite);
	hpSliderFill->GetComponent<Slider>()->SetSprite(hpSliderFillSprite);

	enemy->GetComponent<EnemyController>()->SetSlider(hpSliderFill, hpSliderBackground);

	CurScene->AddGameObject(hpSliderBackground);
	CurScene->AddGameObject(hpSliderFill);
#pragma endregion

	enemy->SetTag(L"Enemy");

	CurScene->AddGameObject(enemy);
}

void EnemySpawnManager::SetTarget(shared_ptr<Transform> target)
{
	m_target = target;
}