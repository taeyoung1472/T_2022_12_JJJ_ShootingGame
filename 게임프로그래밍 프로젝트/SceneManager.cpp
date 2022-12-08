#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Update()
{
	// ���� ��Ƽ��� ���� ������ ���� ����
	if (m_activeScene == nullptr)
		return;

	// Update ���� ����
	m_activeScene->Update();
	m_activeScene->LateUpdate();
	m_activeScene->FinalUpdate();
}

void SceneManager::Render()
{
	// ���� ��Ƽ��� ���� ������ ���� ����
	if (m_activeScene == nullptr)
		return;

	m_activeScene->Render();
}

void SceneManager::LoadScene(wstring sceneName)
{
	// ���� ��Ƽ��� �� ����
	if (m_activeScene != nullptr)
		m_activeScene = nullptr;

	// sceneName �� �̿��Ͽ� map���� ã��
	auto it = m_scenes.find(sceneName);

	if (it != m_scenes.end()) {
		m_activeScene = it->second;
		m_activeScene->Start();
	}
}

void SceneManager::RegisterScene(wstring sceneName, shared_ptr<Scene> scene)
{
	// �̻��� ���� ������ ����
	if (sceneName.empty() || scene == nullptr)
		return;

	scene->Awake();

	m_scenes.insert({sceneName, scene});
}
