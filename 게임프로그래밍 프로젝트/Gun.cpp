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

Gun::Gun()
{
}

Gun::~Gun()
{
}

void Gun::Awake()
{
	shared_ptr<Sprite> gunSprite = ResourceManager::GetInst()->Load<Sprite>(L"GunSprite", L"Sprite\\ARShoot.bmp");
	gunSprite->SetPixelPerfect(64);
	gunSprite->SetRow(16);
	m_gunSprite = gunSprite;

	originPos = GetTransform()->GetLocalPosition();
	knockBackPos = originPos - Vector2(20, 0);

	GetGameObject()->GetComponent<SpriteRendere>(COMPONENT_TYPE::SPRITERENDERE)->SetSprite(m_gunSprite);
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
				m_gunSprite->SetCurRow(i);
				if (i == row) {
					m_gunSprite->SetCurRow(0);
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
		isFire = true;
		m_timer = 0.0f;
	}

	GetTransform()->y = originY + sin(Time->GetTime() * 5) * 5;

	
	WCHAR str[200];

	int angle = 100;
	Vector2 mousePos = Vector2(Input->GetMousePos().x, Input->GetMousePos().y);

	Vector2 dir = Normalize(mousePos - GetTransform()->GetWorldPosition());

	angle = atan2(dir.y, dir.x) * 57.2958f;

	wsprintf(str, L"Angle : %d", angle);
	TextOut(GameLogic::GetInst()->GetHDC(), 10, 10, str, wcslen(str));

	m_timer += Time->GetDeltaTime();
}
