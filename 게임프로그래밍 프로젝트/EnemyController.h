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
	virtual void OnDestroy() override;
	
public:	
	void SetTarget(shared_ptr<Transform> target);
	void Damage(int dmg);
	void SetSlider(shared_ptr<GameObject> fill, shared_ptr<GameObject> background);

private:
	shared_ptr<Sprite> m_enemySprite;
	shared_ptr<Transform> m_targetTransform;

	shared_ptr<GameObject> m_slider;
	shared_ptr<GameObject> m_sliderBackground;

	float m_timer = 0;
	float m_speed = 150;

	bool m_isRight = true;

	int m_hp = 5;

	const float ANIMATION_LOADING_TIME = 0.125f;
};