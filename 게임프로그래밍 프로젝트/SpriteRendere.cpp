#include "pch.h"
#include "SpriteRendere.h"
#include "GameLogic.h"
#include "Transform.h"
#include "Sprite.h"

SpriteRendere::SpriteRendere() : Component(COMPONENT_TYPE::SPRITERENDERE), m_alphaColor{0, 0, 255}
{
}

SpriteRendere::~SpriteRendere()
{
}

void SpriteRendere::Render()
{
	HDC hdc = GameLogic::GetInst()->GetHDC();

	Vector2 pos = GetTransform()->GetWorldPosition();

	Vector2 size = m_sprite->GetSize();

	int curRow = m_sprite->GetCurRow();
	int row = m_sprite->GetRow();
	float fixedPixelPerfect = m_sprite->GetFixedPixelPerfect();

	TransparentBlt(hdc
		, (int)(pos.x - (float)(size.x * fixedPixelPerfect / row / 2))
		, (int)(pos.y - (float)(size.y * fixedPixelPerfect) / 2)
		, (size.x * fixedPixelPerfect) / row, size.y * fixedPixelPerfect
		, m_sprite->GetDC()
		, (size.x / row) * (curRow), 0, size.x / row, size.y,
		RGB_COLOR(m_alphaColor));
}
