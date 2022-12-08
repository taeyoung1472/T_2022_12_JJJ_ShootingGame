#pragma once
#include "Object.h"

enum class COMPONENT_TYPE : UINT8
{
	TRANSFORM,
	COLLIDER,
	SPRITERENDERE,
	MONOBEHAVIOUR,

	END,
};

enum
{
	FIXED_COMPONENT_COUNT = static_cast<UINT8>(COMPONENT_TYPE::END) - 1
};

class GameObject;
class Transform;

class Component : public Object
{
public:
	Component(COMPONENT_TYPE type);
	virtual ~Component();

public:
	virtual void Awake() {}
	virtual void Start() {}
	virtual void Update() {}
	virtual void LateUpdate() {}
	virtual void FinalUpdate() {}
	virtual void Render() {}

public:
	COMPONENT_TYPE GetType() { return m_type; }

	shared_ptr<GameObject> GetGameObject();
	shared_ptr<Transform> GetTransform();

private:
	friend class GameObject;
	void SetGameObject(shared_ptr<GameObject> gameObject) { m_gameObject = gameObject; }

protected:
	COMPONENT_TYPE m_type;
	weak_ptr<GameObject> m_gameObject;
};

