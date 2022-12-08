#pragma once
#include "Component.h"
#include "Object.h"
#include "Transform.h"

class MonoBehaviour;

class GameObject : public Object, public enable_shared_from_this<GameObject>
{
public:
	GameObject();
	virtual ~GameObject();

public:
	void Init();

	template<typename T>
	shared_ptr<T> AddComponent(shared_ptr<Component> component);

	template<typename T>
	shared_ptr<T> GetComponent(COMPONENT_TYPE type);

public:
	shared_ptr<Transform> GetTransform() { return GetComponent<Transform>(COMPONENT_TYPE::TRANSFORM); }

public:
	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void FinalUpdate();
	virtual void Render();

private:
	array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> m_components;
	vector<shared_ptr<MonoBehaviour>> m_scripts;
};

template<typename T>
shared_ptr<T> GameObject::AddComponent(shared_ptr<Component> component)
{
	component->SetGameObject(shared_from_this());

	UINT8 index = static_cast<UINT8>(component->GetType());

	if (index < FIXED_COMPONENT_COUNT)
	{
		m_components[index] = component;
	}
	else
	{
		m_scripts.push_back(dynamic_pointer_cast<MonoBehaviour>(component));
	}

	return static_pointer_cast<T>(component);
}

template<typename T>
shared_ptr<T> GameObject::GetComponent(COMPONENT_TYPE type)
{
	UINT8 index = static_cast<UINT8>(type);

	return static_pointer_cast<T>(m_components[index]);
}