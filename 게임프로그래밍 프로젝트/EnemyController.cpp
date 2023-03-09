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
#include "Slider.h"
#include "Transform.h"

EnemyController::EnemyController()
{

}

EnemyController::~EnemyController()
{

}

void EnemyController::Awake()
{
	shared_ptr<Sprite> IdleSprite = ResourceManager::GetInst()->Load<Sprite>(L"EnemySprite", L"Sprite\\EnemyRun.bmp");
	GetGameObject()->GetComponent<SpriteRendere>()->SetPixelPerfect(16);
	IdleSprite->SetRow(4);
	IdleSprite->SetColumn(2);
	m_enemySprite = IdleSprite;

	m_slider->GetComponent<Slider>()->Init(m_hp);
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

	// ¿À¸¥ÂÊ
	if (GetTransform()->GetWorldPosition().x < m_targetTransform->GetWorldPosition().x && !m_isRight)
	{
		GetGameObject()->GetComponent<SpriteRendere>()->SetColumn(0);

		m_isRight = true;
	}
	// ¿ÞÂÊ
	else if (GetTransform()->GetWorldPosition().x > m_targetTransform->GetWorldPosition().x && m_isRight)
	{
		GetGameObject()->GetComponent<SpriteRendere>()->SetColumn(1);

		m_isRight = false;
	}
}

void EnemyController::OnDestroy()
{
	CurScene->Destroy(m_slider);
	CurScene->Destroy(m_sliderBackground);
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

		if (randIdx <= 15) 
		{
			shared_ptr<GameObject> item = GameObject::Instantiate(GetTransform()->GetWorldPosition());
			
			item->AddComponent<SpriteRendere>();
			item->AddComponent<Item>();
			item->AddComponent<Collider>();
			item->GetComponent<Collider>()->SetSize(Vector2(50, 50));
			item->SetTag(L"Item");

			int randItemIdx = rand.Range(0, (UINT)ITEM_TYPE::END - 1);

			switch (randItemIdx)
			{
			case 0: 
			{
				item->GetComponent<Item>()->SetType(ITEM_TYPE::HP);

				shared_ptr<Sprite> sprite = ResourceManager::GetInst()->Load<Sprite>(L"HpItemSprite", L"Sprite\\HpItem.bmp");
				item->GetComponent<SpriteRendere>()->SetSprite(sprite);
				item->GetComponent<SpriteRendere>()->SetPixelPerfect(45);
			}
			break;
			case 1:
			{
				item->GetComponent<Item>()->SetType(ITEM_TYPE::FIRE_RATE);

				shared_ptr<Sprite> sprite = ResourceManager::GetInst()->Load<Sprite>(L"FireRateItemSprite", L"Sprite\\FireRateItem.bmp");
				item->GetComponent<SpriteRendere>()->SetSprite(sprite);
				item->GetComponent<SpriteRendere>()->SetPixelPerfect(104);
			}
			break;
			case 2:
			{
				item->GetComponent<Item>()->SetType(ITEM_TYPE::SPEED);

				shared_ptr<Sprite> sprite = ResourceManager::GetInst()->Load<Sprite>(L"ItemSpeedSprite", L"Sprite\\ItemSpeed.bmp");
				item->GetComponent<SpriteRendere>()->SetSprite(sprite);
				item->GetComponent<SpriteRendere>()->SetPixelPerfect(62);
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
		m_slider->GetComponent<Slider>()->SetValue(m_hp);
		SoundManager::GetInst()->Play(L"EnemyHit");
	}
}

void EnemyController::SetSlider(shared_ptr<GameObject> fill, shared_ptr<GameObject> background)
{
	m_slider = fill;
	m_sliderBackground = background;
}
