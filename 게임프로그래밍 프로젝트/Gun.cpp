#include "pch.h"
#include "Gun.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "GameObject.h"
#include "SpriteRendere.h"
#include "Sprite.h"
#include "Math.h"
#include "GameLogic.h"
#include "Bullet.h"
#include "Math.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Collider.h"
#include "SoundManager.h"

Gun::Gun()
{
}

Gun::~Gun()
{
}

void Gun::Awake()
{
	SoundManager::GetInst()->LoadSound(L"GunFire", false, L"Audio\\GunFire.wav");
	shared_ptr<Sprite> gunSprite = ResourceManager::GetInst()->Load<Sprite>(L"GunSprite", L"Sprite\\ARShoot.bmp");
	gunSprite->SetPixelPerfect(64);
	gunSprite->SetRow(16);
	m_gunSprite = gunSprite;

	originPos = GetTransform()->GetLocalPosition();
	knockBackPos = originPos - Vector2(20, 0);

	GetGameObject()->GetComponent<SpriteRendere>()->SetSprite(m_gunSprite);
	originY = GetTransform()->y;
}

void Gun::Update()
{
	if (isFire) 
	{
		int row = m_gunSprite->GetRow();
		for (int i = row; i > 0; i--)
		{
			if (m_timer > m_fireDelay * ((float)i / (float)row))
			{
				GetGameObject()->GetComponent<SpriteRendere>()->SetRow(i);
				if (i == row) {
					GetGameObject()->GetComponent<SpriteRendere>()->SetRow(0);
					isFire = false;
				}
				break;
			}

			float lerpValue;
			if (m_timer > m_fireDelay * 0.5f) 
			{
				lerpValue = (m_timer - m_fireDelay * 0.5f) * 2 / m_fireDelay;
				GetTransform()->SetLocalPosition(Lerp(originPos, knockBackPos * m_randKnockbackPower, lerpValue));
			}
			else 
			{
				lerpValue = m_timer * 2 / m_fireDelay;
				GetTransform()->SetLocalPosition(Lerp(knockBackPos * m_randKnockbackPower, originPos, lerpValue));
			}
		}
	}

	if (Input->GetKey(KeyCode::LBUTTON) && m_timer > m_fireDelay && !isFire)
	{
		shared_ptr<GameObject> bullet = GameObject::Instantiate(GetTransform()->GetWorldPosition() + Vector2(40, -10));

		Vector2 dir = Normalize(Vector2(Input->GetMousePos()) - GetTransform()->GetWorldPosition() + Vector2(40, -10));

		bullet->AddComponent<Bullet>(make_shared<Bullet>());
		bullet->GetComponent<Bullet>()->SetDir(dir);
		bullet->GetComponent<Bullet>()->SetSpeed(750);

		bullet->AddComponent<SpriteRendere>(make_shared<SpriteRendere>());
		shared_ptr<Sprite> bulletSprite = ResourceManager::GetInst()->Load<Sprite>(L"BulletSprite", L"Sprite\\Bullet.bmp");
		bulletSprite->SetPixelPerfect(200);
		bullet->GetComponent<SpriteRendere>()->SetSprite(bulletSprite);

		bullet->AddComponent<Collider>(make_shared<Collider>());
		bullet->GetComponent<Collider>()->SetSize(Vector2(25, 25));

		SoundManager::GetInst()->Play(L"GunFire");

		CurScene->AddGameObject(bullet);

		isFire = true;
		m_timer = 0.0f;
	}

	GetTransform()->y = originY + sin(Time->GetTime() * 5) * 5;

	m_timer += Time->GetDeltaTime();
}
