#include "pch.h"
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"

Component::Component() : Object(OBJECT_TYPE::COMPONENT)
{
}

Component::~Component()
{
}

shared_ptr<GameObject> Component::GetGameObject()
{
	return m_gameObject.lock();
}

shared_ptr<Transform> Component::GetTransform()
{
	if (m_transform == nullptr) 
	{
		m_transform = m_gameObject.lock()->GetComponent<Transform>();;
	}
	return m_transform;
}
