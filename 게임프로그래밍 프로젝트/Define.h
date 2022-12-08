#pragma once
#define SINGLE(type) static type* GetInst(){ static type instance; return &instance; }
#define WINDOW_NAME L"Taeyoung Custom Game"

// Manager Define
#define Input InputManager::GetInst()
#define Time TimeManager::GetInst()
#define CurScene SceneManager::GetInst()->GetActiveScene()

#define RGB_COLOR(Color)          ((COLORREF)(((BYTE)(Color.r)|((WORD)((BYTE)(Color.g))<<8))|(((DWORD)(BYTE)(Color.b))<<16)))