#pragma once
#include "Component.h"
#include "Sprite.h"

class SpriteRendere : public Component
{
public:
	SpriteRendere();
	virtual ~SpriteRendere();

public:
	virtual void Render() override;

	Color GetColor() { return m_alphaColor; }
	void SetColor(Color data) { m_alphaColor = data; }

	shared_ptr<Sprite> GetSprite() { return m_sprite; }
	void SetSprite(shared_ptr<Sprite> sprite) { m_sprite = sprite; }

private:
	shared_ptr<Sprite> m_sprite;
	Color m_alphaColor;
};

