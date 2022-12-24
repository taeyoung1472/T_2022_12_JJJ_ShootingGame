#include "pch.h"
#include "Scene.h"
#include "GameObject.h"

void Scene::Awake()
{
	for (const shared_ptr<GameObject>& gameObject : m_gameObjects)
	{
		if (gameObject)
			gameObject->Awake();
	}
}

void Scene::Start()
{
	for (const shared_ptr<GameObject>& gameObject : m_gameObjects)
	{
		if (gameObject)
			gameObject->Start();
	}
}

void Scene::Update()
{
	for (const shared_ptr<GameObject>& gameObject : m_gameObjects)
	{
		if (find(m_gameObjects.begin(), m_gameObjects.end(), gameObject) != m_gameObjects.end()) 
		{
			gameObject->Update();
		}
	}
}

void Scene::LateUpdate()
{
	for (const shared_ptr<GameObject>& gameObject : m_gameObjects)
	{
		if (gameObject)
			gameObject->LateUpdate();
	}
}

void Scene::FinalUpdate()
{
	for (const shared_ptr<GameObject>& gameObject : m_gameObjects)
	{
		if (gameObject)
			gameObject->FinalUpdate();
	}

	DestroyExcute();
}

void Scene::Render()
{
	for (const shared_ptr<GameObject>& gameObject : m_gameObjects)
	{
		if (gameObject)
			gameObject->Render();
	}
}

void Scene::AddGameObject(shared_ptr<GameObject> gameObject)
{
	m_gameObjects.push_back(gameObject);

	// gameObject Start 단계 실행
	gameObject->Awake();
	gameObject->Start();
}

void Scene::Destroy(shared_ptr<GameObject> gameObject)
{
	m_destroyStack.push(gameObject);
}

void Scene::DestroyExcute()
{
	while (!m_destroyStack.empty())
	{
		shared_ptr<GameObject> obj = m_destroyStack.front();

		auto findIt = find(m_gameObjects.begin(), m_gameObjects.end(), obj);

		if (findIt != m_gameObjects.end()) {
			obj->Destroy();
			m_gameObjects.erase(findIt);
		}

		m_destroyStack.pop();
	}
}
