#pragma once
#include "MonoBehaviour.h"
#include "Sprite.h"

class PlayerController : public MonoBehaviour
{
public:
	PlayerController();
	virtual ~PlayerController();

public:
	virtual void Awake() override;
	virtual void Update() override;

private:
	float m_speeed;
	float m_timer;

	float m_animationTimer;

	bool m_isRunning;

	shared_ptr<Sprite> m_runSprite;
	shared_ptr<Sprite> m_idleSprite;

	shared_ptr<Sprite> m_curRenderingSprite;
};

