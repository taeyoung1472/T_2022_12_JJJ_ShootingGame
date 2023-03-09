#pragma once
#include "Component.h"
#include "Object.h"
#include "Transform.h"

class MonoBehaviour;
class Collider;

class GameObject : public Object, public enable_shared_from_this<GameObject>
{
public:
	GameObject();
	virtual ~GameObject();

public:
	void Init();

	template<typename T>
	shared_ptr<T> AddComponent();

	template<typename T>
	shared_ptr<T> GetComponent();

public:
	shared_ptr<Transform> GetTransform() { return GetComponent<Transform>(); }
	static shared_ptr<GameObject> Instantiate(Vector2 pos = Vector2(0, 0), shared_ptr<Transform> parent = nullptr);

public:
	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void FinalUpdate();
	virtual void Render();
	virtual void CollisionEnter(weak_ptr<Collider> collision);

public:
	void Destroy();
	wstring GetTag() { return m_tag; }
	void SetTag(wstring value) { m_tag = value; }

private:
	map<string, shared_ptr<Component>> m_components;
	shared_ptr<Transform> m_transform;
	wstring m_tag;
};

template<typename T>
shared_ptr<T> GameObject::AddComponent()
{
	shared_ptr<Component> component = make_shared<T>();
	component->SetGameObject(shared_from_this());
	m_components.insert({ typeid(T).name(), component});

	return static_pointer_cast<T>(component);
}

template<typename T>
shared_ptr<T> GameObject::GetComponent()
{
	return static_pointer_cast<T>(m_components[typeid(T).name()]);
}