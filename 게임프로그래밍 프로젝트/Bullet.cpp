#include "pch.h"
#include "Bullet.h"
#include "Transform.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameLogic.h"
#include "GameObject.h"
#include "Collider.h"
#include "EnemyController.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::Start()
{
}

void Bullet::Update()
{
	GetTransform()->Translate(m_dir * m_speed * Time->GetDeltaTime());
}

void Bullet::CollisionEnter(weak_ptr<Collider> collision)
{
	wstring targetTag = collision.lock()->GetGameObject()->GetTag();

	if (targetTag == L"Player")
	{
		// DoNothing
	}
	else if (targetTag == L"Enemy")
	{
		collision.lock()->GetGameObject()->GetComponent<EnemyController>()->Damage(1);
		CurScene->Destroy(GetGameObject());
	}
	else {
		CurScene->Destroy(GetGameObject());
	}
}
