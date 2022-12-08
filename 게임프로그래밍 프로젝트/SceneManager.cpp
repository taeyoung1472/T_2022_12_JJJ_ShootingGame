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
	// 현재 엑티브된 씬이 없으면 실행 안함
	if (m_activeScene == nullptr)
		return;

	// Update 순차 실행
	m_activeScene->Update();
	m_activeScene->LateUpdate();
	m_activeScene->FinalUpdate();
}

void SceneManager::Render()
{
	// 현재 엑티브된 씬이 없으면 실행 안함
	if (m_activeScene == nullptr)
		return;

	m_activeScene->Render();
}

void SceneManager::LoadScene(wstring sceneName)
{
	// 현재 엑티브된 씬 정리
	if (m_activeScene != nullptr)
		m_activeScene = nullptr;

	// sceneName 을 이용하여 map에서 찾기
	auto it = m_scenes.find(sceneName);

	if (it != m_scenes.end()) {
		m_activeScene = it->second;
		m_activeScene->Start();
	}
}

void SceneManager::RegisterScene(wstring sceneName, shared_ptr<Scene> scene)
{
	// 이상한 정보 들어오면 리턴
	if (sceneName.empty() || scene == nullptr)
		return;

	scene->Awake();

	m_scenes.insert({sceneName, scene});
}
