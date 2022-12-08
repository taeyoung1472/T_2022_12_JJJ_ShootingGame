#pragma once
#include "pch.h"

class TimeManager
{
public:
	TimeManager();
	~TimeManager();

public:
	void Init();
	void Update();

public:
	SINGLE(TimeManager);

public:
	float GetDeltaTime() { return deltaTime * timeScale; };
	float GetTime() { return time; }
	void SetTimeScale(float value) { timeScale = value; }

private:
	double deltaTime	= 0;
	double timeScale	= 1;
	double time			= 0;

private:
	UINT m_CallCount			= 0;
	double m_TotalDeltaTime		= 0;
	LARGE_INTEGER m_PrevCount	= { };
	LARGE_INTEGER m_CurCount	= { };
	LARGE_INTEGER m_Frequency	= { };
};

