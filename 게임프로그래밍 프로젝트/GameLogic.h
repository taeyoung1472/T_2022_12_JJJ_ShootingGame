#pragma once
#include "BaseWindow.h"

class GameLogic : public BaseWindow
{
private:
	POINT	m_Resolution;
	HDC		m_offHdc;
	HDC		m_memHdc;
	HBITMAP m_offBit;

public:
	SINGLE(GameLogic);

private:
	GameLogic();
	~GameLogic();

public:
	int		Init(HWND _hWnd, POINT _ptResolution);
	void	Progress();
	const	HWND& GetWndHandle() { return m_hWnd; }
	const	POINT& GetResolution() { return m_Resolution; }

	const   HDC GetHDC() { return m_memHdc; }
	const   HDC GetOffHDC() { return m_offHdc; }

	const   HBITMAP GetOffBit() { return m_offBit; }

private:
	void	Update();
	void	Render();
};

