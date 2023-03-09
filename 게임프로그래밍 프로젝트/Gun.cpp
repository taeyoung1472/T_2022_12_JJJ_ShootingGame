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

Gun::Gun() : m_damage(1), m_firePos(40, -10)
{
}

Gun::~Gun()
{
}

void Gun::Awake()
{
	SoundManager::GetInst()->LoadSound(L"GunFire", false, L"Audio\\GunFire.wav");
	shared_ptr<Sprite> gunSprite = ResourceManager::GetInst()->Load<Sprite>(L"GunSprite", L"Sprite\\ARShoot.bmp");
	gunSprite->SetColumn(2);
	gunSprite->SetRow(16);
	m_gunSprite = gunSprite;

	m_originPos = GetTransform()->GetLocalPosition();
	m_knockBackPos = m_originPos - Vector2(20, 0);

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
				GetTransform()->SetLocalPosition(Lerp(m_originPos, m_knockBackPos * m_randKnockbackPower, lerpValue));
			}
			else 
			{
				lerpValue = m_timer * 2 / m_fireDelay;
				GetTransform()->SetLocalPosition(Lerp(m_knockBackPos * m_randKnockbackPower, m_originPos, lerpValue));
			}
		}
	}

	if (Input->GetKey(KeyCode::LBUTTON) && m_timer > m_fireDelay && !isFire)
	{
		shared_ptr<GameObject> bullet = GameObject::Instantiate(GetTransform()->GetWorldPosition() + m_firePos);

		Vector2 dir = Normalize(Vector2(Input->GetMousePos()) - (GetTransform()->GetWorldPosition() + m_firePos));

		bullet->AddComponent<Bullet>();
		bullet->GetComponent<Bullet>()->SetDir(dir);
		bullet->GetComponent<Bullet>()->SetSpeed(750);
		bullet->GetComponent<Bullet>()->SetDamage(m_damage);

		bullet->AddComponent<SpriteRendere>();
		shared_ptr<Sprite> bulletSprite = ResourceManager::GetInst()->Load<Sprite>(L"BulletSprite", L"Sprite\\Bullet.bmp");
		bullet->GetComponent<SpriteRendere>()->SetSprite(bulletSprite);
		bullet->GetComponent<SpriteRendere>()->SetPixelPerfect(200);

		bullet->AddComponent<Collider>();
		bullet->GetComponent<Collider>()->SetSize(Vector2(25, 25));

		bullet->SetTag(L"Bullet");

		SoundManager::GetInst()->Play(L"GunFire");

		CurScene->AddGameObject(bullet);

		isFire = true;
		m_timer = 0.0f;
	}

	GetTransform()->y = originY + sin(Time->GetTime() * 5) * 5;

	m_timer += Time->GetDeltaTime();
}

void Gun::SetOriginPosAndKnockBackPosAndFirePos(Vector2 origin, Vector2 knockBack, Vector2 firePos)
{
	m_originPos = origin;
	m_knockBackPos = knockBack;
	m_firePos = firePos;
}

void Gun::FireRateUpgrade()
{
	m_fireDelay -= 0.02f;

	if (m_fireDelay <= 0.07f) {
		if (m_damage == 2) 
		{
			m_fireDelay = 0.06f;
		}
		else 
		{
			m_fireDelay = 0.12f;
			m_damage++;
		}
	}
}
