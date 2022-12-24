#pragma once
#include "Define.h"

class GameObject;

class Scene
{
public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();
	void Render();

public:
	void AddGameObject(shared_ptr<GameObject> gameObject);
	void Destroy(shared_ptr<GameObject> gameObject);
	void DestroyExcute();

private:
	vector<shared_ptr<GameObject>> m_gameObjects;
	queue<shared_ptr<GameObject>> m_destroyStack;
};

