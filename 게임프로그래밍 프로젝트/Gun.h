#pragma once
#include "MonoBehaviour.h"
#include "Sprite.h"

class Gun : public MonoBehaviour
{
public:
	Gun();
	~Gun();

public:
	virtual void Awake() override;
	virtual void Update() override;

private:
	bool isFire = false;
	float m_timer = 0.0f;

	float originY;

	float m_fireDelay = 0.12f;
	float m_randKnockbackPower = 1.0f;

	Vector2 knockBackPos;
	Vector2 originPos;

	shared_ptr<Sprite> m_gunSprite;
};

