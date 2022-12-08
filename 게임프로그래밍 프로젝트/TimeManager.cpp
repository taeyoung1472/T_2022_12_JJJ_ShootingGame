#include "pch.h"
#include "TimeManager.h"
#include "GameLogic.h"

TimeManager::TimeManager()
{
}

TimeManager::~TimeManager()
{
}

void TimeManager::Init()
{
	// cpu틱을 센다
	QueryPerformanceCounter(&m_PrevCount);
	// 초당 카운트 횟수를 반환
	QueryPerformanceFrequency(&m_Frequency);
}

void TimeManager::Update()
{
	QueryPerformanceCounter(&m_CurCount);
	// 현재 프레임과 이전프레임 사이의 시간을 구한다
	deltaTime = static_cast<double>(m_CurCount.QuadPart - m_PrevCount.QuadPart) / static_cast<double>(m_Frequency.QuadPart);

	m_PrevCount = m_CurCount;
	++m_CallCount;
	m_TotalDeltaTime += deltaTime;
	if (m_TotalDeltaTime >= 1)
	{
		static wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d", m_CallCount);

		SetWindowText(GameLogic::GetInst()->GetWndHandle(), szBuffer);

		m_CallCount = 0;
		m_TotalDeltaTime = 0;
	}

	time += deltaTime;
}
