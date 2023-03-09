#pragma once
#include "Object.h"

class GameObject;
class Transform;
class Collider;

class Component : public Object
{
public:
	Component();
	virtual ~Component();

public:
	virtual void Awake() {}
	virtual void Start() {}
	virtual void Update() {}
	virtual void LateUpdate() {}
	virtual void FinalUpdate() {}
	virtual void Render() {}

	virtual void OnDestroy() {}

public:
	virtual void CollisionEnter(weak_ptr<Collider> collision) {}

public:
	shared_ptr<GameObject> GetGameObject();
	shared_ptr<Transform> GetTransform();

private:
	friend class GameObject;
	void SetGameObject(shared_ptr<GameObject> gameObject) { m_gameObject = gameObject; }

protected:
	weak_ptr<GameObject> m_gameObject;

private:
	shared_ptr<Transform> m_transform;
};

