#include "pch.h"
#include "Collider.h"
#include "GameLogic.h"
#include "PhysicsManager.h"

Collider::Collider() : Component()
{
}

Collider::~Collider()
{
}

void Collider::Awake()
{
	PhysicsManager::GetInst()->RegistCollision(shared_from_this());
}

void Collider::Render()
{
	// DEBUG

	//HDC dc = GameLogic::GetInst()->GetOffHDC();
	//Vector2 pos = GetPos();

	//Rectangle(dc, pos.x - m_size.x / 2, pos.y + m_size.y / 2, pos.x + m_size.x / 2, pos.y - m_size.y / 2);
}

void Collider::OnDestroy()
{
	PhysicsManager::GetInst()->RemoveCollision(shared_from_this());
}
