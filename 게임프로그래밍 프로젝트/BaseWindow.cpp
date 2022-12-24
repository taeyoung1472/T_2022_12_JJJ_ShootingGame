#include "pch.h"
#include "BaseWindow.h"
#include "GameLogic.h"

BaseWindow::BaseWindow()
{
}

BaseWindow::~BaseWindow()
{
}

int BaseWindow::Run(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    m_hInstance = hInstance;
    this->MyRegisterClass();
    this->WindowCreate();
    this->WindowShow(nCmdShow);
    this->WindowUpdate();

    if (FAILED(GameLogic::GetInst()->Init(m_hWnd, POINT{1280, 720}))) {
        MessageBox(m_hWnd, L"Core 생성 실패", L"ERROR", MB_OK);
        return FALSE;
    }

    return this->MessageLoop();
}

ATOM BaseWindow::MyRegisterClass()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = BaseWindow::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_hInstance;
    wcex.hIcon = LoadIcon(m_hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = WINDOW_NAME;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    return RegisterClassExW(&wcex);
}

void BaseWindow::WindowCreate()
{
    m_hWnd = CreateWindowW(WINDOW_NAME, L"Game", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInstance, nullptr);
}

void BaseWindow::WindowShow(int nCmdShow)
{
    ShowWindow(m_hWnd, nCmdShow);
}

void BaseWindow::WindowUpdate()
{
    UpdateWindow(m_hWnd);
}

LRESULT BaseWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int BaseWindow::MessageLoop()
{
    MSG msg;
    memset(&msg, 0, sizeof(msg));

    // PeekMessage
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message) {
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            // 메시지가 들어오지 않은경우 -> 게임 로직 실행
            GameLogic::GetInst()->Progress();
        }
    }
    return (int)msg.wParam;
}
