#pragma once
#include "framework.h"

class BaseWindow
{
public:
	BaseWindow();
	~BaseWindow();

public:
	int							Run(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow);

private:
	ATOM					    MyRegisterClass();
	void						WindowCreate();
	void						WindowShow(int mCmdShow);
	void						WindowUpdate();
	static LRESULT CALLBACK		WndProc(HWND, UINT, WPARAM, LPARAM);
	int							MessageLoop();

protected:
	HWND				m_hWnd;
	HINSTANCE			m_hInstance;
};

