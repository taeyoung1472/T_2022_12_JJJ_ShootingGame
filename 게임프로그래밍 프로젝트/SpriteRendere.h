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

	void MoveRow(int index) { m_curRow = (m_curRow + index) % m_sprite->GetRow(); }
	void SetRow(int index) { m_curRow = index; }

	void MoveColumn(int index) { m_curColumn = (m_curColumn + index) % m_sprite->GetColumn(); }
	void SetColumn(int index) { m_curColumn = index; }

	void SetPixelPerfect(const int& value);
	float GetFixedPixelPerfect();

protected:
	shared_ptr<Sprite> m_sprite;
	Color m_alphaColor;
	int m_curRow = 0;
	int m_curColumn = 0;
	int m_pixelPerfect;
};

