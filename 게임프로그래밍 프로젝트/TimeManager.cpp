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
	// cpuƽ�� ����
	QueryPerformanceCounter(&m_PrevCount);
	// �ʴ� ī��Ʈ Ƚ���� ��ȯ
	QueryPerformanceFrequency(&m_Frequency);
}

void TimeManager::Update()
{
	QueryPerformanceCounter(&m_CurCount);
	// ���� �����Ӱ� ���������� ������ �ð��� ���Ѵ�
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
