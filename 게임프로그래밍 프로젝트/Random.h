#pragma once
#include "pch.h"
#include <random>

struct Random
{
public:
	Random() 
	{
		mt19937 gen(rd());
		m_gen = gen;
	}

	int Range(int min, int max) 
	{
        uniform_int_distribution<int> dis(min, max);

		return dis(m_gen);
	}
	float Range(float min, float max)
	{
		uniform_int_distribution<int> dis(min, max);

		return dis(m_gen);
	}

private:
	random_device rd;
	mt19937 m_gen;
};