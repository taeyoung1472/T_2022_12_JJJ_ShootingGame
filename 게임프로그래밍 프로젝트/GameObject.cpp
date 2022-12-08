#include "pch.h"
#include "GameObject.h"
#include "Component.h"
#include "MonoBehaviour.h"
#include "Transform.h"

GameObject::GameObject() : Object(OBJECT_TYPE::GAMEOBJECT)
{
	Awake();
}

GameObject::~GameObject()
{
}

void GameObject::Init()
{
}

void GameObject::Awake()
{
	for (shared_ptr<Component>& component : m_components)
	{
		if (component)
			component->Awake();
	}

	for (shared_ptr<MonoBehaviour>& script : m_scripts)
	{
		if (script)
			script->Awake();
	}
}

void GameObject::Start()
{
	for (shared_ptr<Component>& component : m_components)
	{
		if (component)
			component->Start();
	}

	for (shared_ptr<MonoBehaviour>& script : m_scripts)
	{
		if (script)
			script->Start();
	}
}

void GameObject::Update()
{
	for (shared_ptr<Component>& component : m_components)
	{
		if (component)
			component->Update();
	}

	for (shared_ptr<MonoBehaviour>& script : m_scripts)
	{
		if (script)
			script->Update();
	}
}

void GameObject::LateUpdate()
{
	for (shared_ptr<Component>& component : m_components)
	{
		if (component)
			component->LateUpdate();
	}

	for (shared_ptr<MonoBehaviour>& script : m_scripts)
	{
		if (script)
			script->LateUpdate();
	}
}

void GameObject::FinalUpdate()
{
	for (shared_ptr<Component>& component : m_components)
	{
		if (component)
			component->FinalUpdate();
	}

	for (shared_ptr<MonoBehaviour>& script : m_scripts)
	{
		if (script)
			script->FinalUpdate();
	}
}

void GameObject::Render()
{
	for (shared_ptr<Component>& component : m_components)
	{
		if (component)
			component->Render();
	}

	for (shared_ptr<MonoBehaviour>& script : m_scripts)
	{
		if (script)
			script->Render();
	}
}