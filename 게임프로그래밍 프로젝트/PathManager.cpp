#include "pch.h"
#include "PathManager.h"
#include "GameLogic.h"

PathManager::PathManager() : m_ResourcePath{}
{
}

PathManager::~PathManager()
{
}

void PathManager::Init()
{
	GetCurrentDirectory(255, m_ResourcePath);
	int Length = wcslen(m_ResourcePath);
	for (int i = Length - 1; i >= 0; i--)
	{
		if (m_ResourcePath[i] == '\\')
		{
			m_ResourcePath[i] = '\0';
			break;
		}
	}
	wcscat_s(m_ResourcePath, 255, L"\\Resources\\");
	SetWindowText(GameLogic::GetInst()->GetWndHandle(), m_ResourcePath);
}
