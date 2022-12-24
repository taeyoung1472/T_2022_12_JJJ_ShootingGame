#include "pch.h"
#include "Slider.h"
#include "Transform.h"
#include "GameObject.h"
#include "Sprite.h"
#include "GameLogic.h"

Slider::Slider()
{
}

Slider::~Slider()
{
}

void Slider::Init(int max)
{
	maxValue = max;

	SetValue(maxValue);

	m_sprite->SetRow(maxValue);
}

void Slider::SetValue(int value)
{
	if (value > maxValue) return;

	curValue = value;
	m_curRow = value;
}

void Slider::Render()
{
	HDC offHdc = Logic->GetOffHDC();
	HWND mHwnd = Logic->GetWndHandle();

	Vector2 pos = GetTransform()->GetWorldPosition();
	Vector2 size = m_sprite->GetSize();

	float fixedPixelPerfect = m_sprite->GetFixedPixelPerfect();

	RECT Rt;
	GetClientRect(mHwnd, &Rt);

	TransparentBlt(offHdc
		, (int)(pos.x - (float)(size.x * fixedPixelPerfect / 2))
		, (int)(pos.y - (float)(size.y * fixedPixelPerfect) / 2)
		, (size.x * ((float)m_curRow / (float)maxValue)) * fixedPixelPerfect
		, size.y * fixedPixelPerfect
		, m_sprite->GetDC()
		, 0
		, 0
		, (size.x * ((float)m_curRow / (float)maxValue))
		, size.y
		, RGB_COLOR(m_alphaColor));
}
