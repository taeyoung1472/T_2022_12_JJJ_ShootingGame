#pragma once
#include "Component.h"
#include "Transform.h"

class Collider : public Component, public std::enable_shared_from_this<Collider>
{
public:
	Collider();
	virtual ~Collider();

public:
	virtual void Awake() override;
	virtual void Render() override;
	
	virtual void OnDestroy() override;

public:
	Vector2 GetPos() { return GetTransform()->GetWorldPosition() + m_center; }
	Vector2 GetSize() { return m_size; }
	void SetCenter(Vector2 value) { m_center = value; }
	void SetSize(Vector2 value) { m_size = value; }

private:
	Vector2 m_size;
	Vector2 m_center;
};

