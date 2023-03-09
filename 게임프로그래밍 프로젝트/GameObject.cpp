#include "pch.h"
#include "GameObject.h"
#include "Component.h"
#include "MonoBehaviour.h"
#include "Transform.h"
#include "SceneManager.h"

GameObject::GameObject() : Object(OBJECT_TYPE::GAMEOBJECT), m_tag(L"Default")
{
	Awake();
}

GameObject::~GameObject()
{
}

void GameObject::Init()
{
}

shared_ptr<GameObject> GameObject::Instantiate(Vector2 pos, shared_ptr<Transform> parent)
{
	shared_ptr<GameObject> object = make_shared<GameObject>();
	object->AddComponent<Transform>();
	object->GetTransform()->SetWorldPosition(pos);
	if (parent != nullptr) {
		object->GetTransform()->SetParent(parent);
		object->GetTransform()->SetLocalPosition(pos);
	}

	return object;
}

void GameObject::Awake()
{
	map<string, shared_ptr<Component>>::iterator  i;
	for (i = m_components.begin(); i != m_components.end(); i++) {
		i->second->Awake();
	}
}

void GameObject::Start()
{
	map<string, shared_ptr<Component>>::iterator  i;
	for (i = m_components.begin(); i != m_components.end(); i++) {
		i->second->Start();
	}
}

void GameObject::Update()
{
	map<string, shared_ptr<Component>>::iterator  i;
	for (i = m_components.begin(); i != m_components.end(); i++) {
		i->second->Update();
	}
}

void GameObject::LateUpdate()
{
	map<string, shared_ptr<Component>>::iterator  i;
	for (i = m_components.begin(); i != m_components.end(); i++) {
		i->second->LateUpdate();
	}
}

void GameObject::FinalUpdate()
{
	map<string, shared_ptr<Component>>::iterator  i;
	for (i = m_components.begin(); i != m_components.end(); i++) {
		i->second->FinalUpdate();
	}
}

void GameObject::Render()
{
	map<string, shared_ptr<Component>>::iterator  i;
	for (i = m_components.begin(); i != m_components.end(); i++) {
		i->second->Render();
	}
}

void GameObject::CollisionEnter(weak_ptr<Collider> collision)
{
	map<string, shared_ptr<Component>>::iterator  i;
	for (i = m_components.begin(); i != m_components.end(); i++) {
		i->second->CollisionEnter(collision);
	}
}

void GameObject::Destroy()
{
	map<string, shared_ptr<Component>>::iterator  i;
	for (i = m_components.begin(); i != m_components.end(); i++) {
		i->second->OnDestroy();
	}
}
