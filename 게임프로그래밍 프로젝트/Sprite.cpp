#include "pch.h"
#include "Sprite.h"
#include "GameLogic.h"

Sprite::Sprite() : Object(OBJECT_TYPE::IMAGE), m_hDC(0), m_row(1), m_Column(1)
{

}

Sprite::~Sprite()
{
}

BITMAP Sprite::GetSprite()
{
	return m_spriteInfo;
}

void Sprite::SetSprite(const wstring& filePath)
{
	m_sprite = (HBITMAP)LoadImage(nullptr, filePath.c_str()
		, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	assert(m_sprite);

	m_hDC = CreateCompatibleDC(GameLogic::GetInst()->GetHDC());
	SelectObject(m_hDC, m_sprite);

	GetObject(m_sprite, sizeof(BITMAP), &m_spriteInfo);
}

void Sprite::SetRow(const int& value)
{
	m_row = value;
}

int Sprite::GetRow()
{
	return m_row;
}

void Sprite::SetColumn(const int& value)
{
	m_Column = value;
}

int Sprite::GetColumn()
{
	return m_Column;
}

Vector2 Sprite::GetSize()
{
	Vector2 returnValue;

	returnValue.x = m_spriteInfo.bmWidth;
	returnValue.y = m_spriteInfo.bmHeight;

	return returnValue;
}