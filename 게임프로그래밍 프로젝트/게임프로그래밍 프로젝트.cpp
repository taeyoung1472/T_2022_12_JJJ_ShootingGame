// 게임프로그래밍 프로젝트.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "게임프로그래밍 프로젝트.h"
#include "pch.h"
#include "BaseWindow.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    BaseWindow game;
    game.Run(hInstance, lpCmdLine, nCmdShow);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    return TRUE;
}