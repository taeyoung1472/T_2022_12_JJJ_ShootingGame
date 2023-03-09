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
	
	void SetOriginPosAndKnockBackPosAndFirePos(Vector2 origin, Vector2 knockBack, Vector2 firePos);

public:
	void FireRateUpgrade();

private:
	bool isFire = false;
	float m_timer = 0.0f;
	int m_damage;

	float originY;

	float m_fireDelay = 0.12f;
	float m_randKnockbackPower = 1.0f;

	Vector2 m_knockBackPos;
	Vector2 m_originPos;
	Vector2 m_firePos;

	shared_ptr<Sprite> m_gunSprite;
};

