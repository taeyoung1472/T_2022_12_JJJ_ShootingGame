#pragma once
#include "MonoBehaviour.h"
#include "Sprite.h"
#include "Item.h"
class Slider;
class Gun;
class Transform;

class PlayerController : public MonoBehaviour
{
public:
	PlayerController();
	virtual ~PlayerController();

public:
	virtual void Awake() override;
	virtual void Update() override;

	virtual void CollisionEnter(weak_ptr<Collider> collision) override;

public:
	void SetHpSlider(shared_ptr<Slider> slider);
	void SetGun(shared_ptr<Gun> gun);
	void SetHand(shared_ptr<Transform> LHand, shared_ptr<Transform> RHand);
	void Damaged(int dmg);
	void GetItem(ITEM_TYPE type);

private:
	int m_stepIndex;

	int m_hp;
	int m_maxHp = 5;

	float m_speed;
	float m_timer;

	float m_stepTimer;
	float m_stepDelay;

	float m_animationTimer;

	bool m_isRunning;
	bool m_isRight = true;

	shared_ptr<Sprite> m_runSprite;
	shared_ptr<Sprite> m_idleSprite;

	shared_ptr<Sprite> m_curRenderingSprite;

	shared_ptr<Slider> m_hpSlider;

	shared_ptr<Gun> m_gun;

	shared_ptr<Transform> m_LHand;
	shared_ptr<Transform> m_RHand;

	Vector2 m_LhandOriginPos;
	Vector2 m_RhandOriginPos;

	Vector2 m_gunOriginPos;
};

