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
	void SetPixelPerfect(const int& value);
	float GetFixedPixelPerfect();

	void SetRow(const int& value);
	int GetRow();

	Vector2 GetSize();

	HDC GetDC() { return m_hDC; }
	HBITMAP GetBit() { return m_sprite; }

private:
	HDC         m_hDC;
	HBITMAP		m_sprite;
	BITMAP		m_spriteInfo;

	POINT m_vertices[3];

	int m_pixelPerfect = 100;
	int m_row = 1;
};

