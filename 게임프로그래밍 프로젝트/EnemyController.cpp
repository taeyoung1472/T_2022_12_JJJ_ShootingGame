#include "pch.h"
#include "EnemyController.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "GameObject.h"
#include "SpriteRendere.h"
#include "Sprite.h"
#include "Math.h"
#include "Scene.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "Item.h"
#include "Collider.h"
#include "Random.h"

EnemyController::EnemyController()
{

}

EnemyController::~EnemyController()
{

}

void EnemyController::Awake()
{
	shared_ptr<Sprite> IdleSprite = ResourceManager::GetInst()->Load<Sprite>(L"EnemySprite", L"Sprite\\EnemyRun.bmp");
	IdleSprite->SetPixelPerfect(16);
	IdleSprite->SetRow(4);
	m_enemySprite = IdleSprite;
}

void EnemyController::Update()
{
	m_timer += Time->GetDeltaTime();
	GetTransform()->Translate(Normalize(m_targetTransform->GetWorldPosition() - GetTransform()->GetWorldPosition()) * m_speed * Time->GetDeltaTime());
	if (m_timer >= ANIMATION_LOADING_TIME)
	{
		m_timer = 0;
		GetGameObject()->GetComponent<SpriteRendere>()->MoveRow(1);
	}
}

void EnemyController::SetTarget(shared_ptr<Transform> target)
{
	m_targetTransform = target;
}

void EnemyController::Damage(int dmg)
{
	m_hp -= dmg;
	if (m_hp <= 0) {

		Random rand;
		int randIdx = rand.Range(0, 100);

		if (randIdx <= 100) 
		{
			shared_ptr<GameObject> item = GameObject::Instantiate(GetTransform()->GetWorldPosition());
			
			item->AddComponent<SpriteRendere>(make_shared<SpriteRendere>());
			item->AddComponent<Item>(make_shared<Item>());
			item->AddComponent<Collider>(make_shared<Collider>());
			item->GetComponent<Collider>()->SetSize(Vector2(50, 50));

			int randItemIdx = rand.Range(0, (UINT)ITEM_TYPE::END - 1);

			switch (randItemIdx)
			{
			case 0: 
			{
				item->GetComponent<Item>()->SetType(ITEM_TYPE::HP);

				shared_ptr<Sprite> sprite = ResourceManager::GetInst()->Load<Sprite>(L"HpItemSprite", L"Sprite\\HpItem.bmp");
				sprite->SetPixelPerfect(45);
				item->GetComponent<SpriteRendere>()->SetSprite(sprite);
			}
			break;
			case 1:
			{
				item->GetComponent<Item>()->SetType(ITEM_TYPE::OTHER1);

				shared_ptr<Sprite> sprite = ResourceManager::GetInst()->Load<Sprite>(L"OtherItemSprite", L"Sprite\\OtherItem.bmp");
				sprite->SetPixelPerfect(120);
				item->GetComponent<SpriteRendere>()->SetSprite(sprite);
			}
			break;
			case 2:
			{
				item->GetComponent<Item>()->SetType(ITEM_TYPE::OTHER2);

				shared_ptr<Sprite> sprite = ResourceManager::GetInst()->Load<Sprite>(L"OtherItemSprite", L"Sprite\\OtherItem.bmp");
				sprite->SetPixelPerfect(120);
				item->GetComponent<SpriteRendere>()->SetSprite(sprite);
			}
			break;
			default:
				break;
			}

			CurScene->AddGameObject(item);
		}

		CurScene->Destroy(GetGameObject());
		SoundManager::GetInst()->Play(L"EnemyDie");
	}
	else {
		SoundManager::GetInst()->Play(L"EnemyHit");
	}
}
