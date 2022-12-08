#pragma once
#include "Component.h"

class Transform : public Component, public enable_shared_from_this<Transform>
{
public:
	Transform();
	virtual ~Transform();

public:
	void Translate(Vector2 dir) { x += dir.x; y += dir.y; }
	Vector2 GetLocalPosition() { return Vector2{ x, y }; }
	Vector2 GetWorldPosition();
	void SetLocalPosition(Vector2 value);
	void SetWorldPosition(Vector2 value);

	float GetAngle() { return m_angle; }
	void SetLocalAngle(float angle) { m_angle = angle; }
	void SetWorldAngle(float angle);

	bool FlagParent() { if (m_parent == nullptr) return false; else { return true; } }
	shared_ptr<Transform> GetParent() { return m_parent; }
	void SetParent(shared_ptr<Transform> value) { m_parent = value; }

public:
	float x;
	float y;

	float m_angle;

private:
	shared_ptr<Transform> m_parent;
};

