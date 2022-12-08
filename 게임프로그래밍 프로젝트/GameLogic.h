#pragma once
#include "BaseWindow.h"

class GameLogic : public BaseWindow
{
private:
	POINT	m_Resolution;
	HDC		m_memDC;
	HDC		m_hDC;
	HBITMAP	m_hBit;
	//HDC		m_memDC;
	//HBITMAP m_hBit;

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

	const   HDC GetHDC() { return m_hDC; }
	const   HDC GetMEMDC() { return m_memDC; }

private:
	void	Update();
	void	Render();
};

