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
		m_timer = 0;
		SpawnEnmey();
	}
}

void EnemySpawnManager::SpawnEnmey()
{
	shared_ptr<GameObject> enemy = make_shared<GameObject>();
	enemy->AddComponent<Transform>(make_shared<Transform>());
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

	enemy->AddComponent<EnemyController>(make_shared<EnemyController>());
	enemy->GetComponent<EnemyController>()->SetTarget(m_target);

	enemy->AddComponent<SpriteRendere>(make_shared<SpriteRendere>());
	shared_ptr<Sprite> enemySprite = ResourceManager::GetInst()->Load<Sprite>(L"EnemySprite", L"Sprite\\EnemyRun.bmp");
	enemySprite->SetPixelPerfect(16);
	enemySprite->SetRow(4);
	enemy->GetComponent<SpriteRendere>()->SetSprite(enemySprite);

	enemy->AddComponent<Collider>(make_shared<Collider>());
	enemy->GetComponent<Collider>()->SetSize(Vector2(75, 120));

	enemy->SetTag(L"Enemy");

	CurScene->AddGameObject(enemy);
}

void EnemySpawnManager::SetTarget(shared_ptr<Transform> target)
{
	m_target = target;
}