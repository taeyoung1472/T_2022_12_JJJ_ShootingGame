#pragma once
#include "MonoBehaviour.h"

class Collider;

class Bullet : public MonoBehaviour
{
public:
	Bullet();
	virtual ~Bullet();

public:
	void SetSpeed(float value) { m_speed = value; }
	void SetDir(Vector2 value) { m_dir = value; }
	void SetDamage(int value) { m_damage = value; }

public:
	virtual void Start() override;
	virtual void Update() override;

	virtual void CollisionEnter(weak_ptr<Collider> collision) override;

private:
	int m_damage;
	float m_speed;
	Vector2 m_dir;
};

