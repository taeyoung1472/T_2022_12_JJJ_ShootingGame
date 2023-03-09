#include "pch.h"
#include "SpriteRendere.h"
#include "GameLogic.h"
#include "Transform.h"
#include "Sprite.h"

SpriteRendere::SpriteRendere() : Component(), m_alphaColor{0, 0, 255}, m_pixelPerfect(100), m_curRow(0), m_curColumn(0)
{
}

SpriteRendere::~SpriteRendere()
{
}

void SpriteRendere::Render()
{
	HDC memHdc = Logic->GetHDC();
    HDC offHdc = Logic->GetOffHDC();
    HBITMAP memBit = m_sprite->GetBit();
    HWND mHwnd = Logic->GetWndHandle();

    float rotation = GetTransform()->GetWorldRotation();
	Vector2 pos = GetTransform()->GetWorldPosition();
	Vector2 size = m_sprite->GetSize();

	int row = m_sprite->GetRow();
	int column = m_sprite->GetColumn();
	float fixedPixelPerfect = GetFixedPixelPerfect();

	RECT Rt;
	GetClientRect(mHwnd, &Rt);

	TransparentBlt(offHdc
		, (int)(pos.x - (float)(size.x * fixedPixelPerfect / row / 2))
		, (int)(pos.y - (float)(size.y * fixedPixelPerfect / column) / 2)
		, (size.x * fixedPixelPerfect) / row, (size.y * fixedPixelPerfect) / column
		, m_sprite->GetDC()
		, (size.x / row) * (m_curRow), (size.y / column) * (m_curColumn), size.x / row, size.y / column,
		RGB_COLOR(m_alphaColor));
}

void SpriteRendere::SetPixelPerfect(const int& value)
{
	m_pixelPerfect = value;
}

float SpriteRendere::GetFixedPixelPerfect()
{
	return 100.0f / m_pixelPerfect;
}
