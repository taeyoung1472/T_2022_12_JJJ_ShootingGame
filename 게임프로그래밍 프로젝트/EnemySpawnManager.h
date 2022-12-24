#pragma once
#include "pch.h"
class Transform;
class Enemy;

class EnemySpawnManager
{
private:
	EnemySpawnManager();
	~EnemySpawnManager();
public:
	SINGLE(EnemySpawnManager)
public:
	void Init();
	void Update();
	void SpawnEnmey();
	void SetTarget(shared_ptr<Transform> target);
private:
	const float SPAWN_COOL = 5;
	float m_timer = 0;

	shared_ptr<Transform> m_target;
};