#pragma once
#include "MonoBehaviour.h"
#include "Sprite.h"

class PlayerController;
class EnemyController : public MonoBehaviour
{
public:
	EnemyController();
	~EnemyController();
public:
	virtual void Awake() override;
	virtual void Update() override;
	
public:	
	void SetTarget(shared_ptr<Transform> target);
	void Damage(int dmg);

private:
	shared_ptr<Sprite> m_enemySprite;
	shared_ptr<Transform> m_targetTransform;
	float m_timer = 0;
	float m_speed = 150;

	int m_hp = 5;

	const float ANIMATION_LOADING_TIME = 0.125f;
};