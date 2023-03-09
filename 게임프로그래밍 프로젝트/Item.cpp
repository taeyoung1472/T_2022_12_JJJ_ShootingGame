#include "pch.h"
#include "Item.h"
#include "Collider.h"
#include "GameObject.h"
#include "PlayerController.h"
#include "Scene.h"
#include "SceneManager.h"

Item::Item()
{
}

Item::~Item()
{
}

void Item::CollisionEnter(weak_ptr<Collider> collision)
{
	if (collision.lock()->GetGameObject()->GetTag() == L"Player") 
	{
		collision.lock()->GetGameObject()->GetComponent<PlayerController>()->GetItem(m_type);
		CurScene->Destroy(GetGameObject());
	}
}
