#include "pch.h"
#include "SpriteRendere.h"
#include "GameLogic.h"
#include "Transform.h"
#include "Sprite.h"

SpriteRendere::SpriteRendere() : Component(), m_alphaColor{0, 0, 255}
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
	float fixedPixelPerfect = m_sprite->GetFixedPixelPerfect();

	RECT Rt;
	GetClientRect(mHwnd, &Rt);

	TransparentBlt(offHdc
		, (int)(pos.x - (float)(size.x * fixedPixelPerfect / row / 2))
		, (int)(pos.y - (float)(size.y * fixedPixelPerfect) / 2)
		, (size.x * fixedPixelPerfect) / row, size.y * fixedPixelPerfect
		, m_sprite->GetDC()
		, (size.x / row) * (m_curRow), 0, size.x / row, size.y,
		RGB_COLOR(m_alphaColor));
}