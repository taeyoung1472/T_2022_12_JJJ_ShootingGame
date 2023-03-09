#pragma once
#include "Object.h"

class Sprite : public Object
{
public:
	Sprite();
	virtual ~Sprite();

public:
	BITMAP GetSprite();
	void SetSprite(const wstring& filePath);

	void SetRow(const int& value);
	int GetRow();
	void SetColumn(const int& value);
	int GetColumn();

	Vector2 GetSize();

	HDC GetDC() { return m_hDC; }
	HBITMAP GetBit() { return m_sprite; }

private:
	HDC         m_hDC;
	HBITMAP		m_sprite;
	BITMAP		m_spriteInfo;
	int m_row;
	int m_Column;
};

