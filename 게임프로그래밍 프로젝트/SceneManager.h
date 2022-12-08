#pragma once
#include "pch.h"

class Scene;

class SceneManager
{
private:
	SceneManager();
	~SceneManager();

public:
	SINGLE(SceneManager);

public:
	void Update();
	void Render();

public:
	void LoadScene(wstring sceneName);
	void RegisterScene(wstring sceneName, shared_ptr<Scene> scene);

public:
	shared_ptr<Scene> GetActiveScene() { return m_activeScene; }

private:
	shared_ptr<Scene>				m_activeScene; // ÇöÀç ¿¢Æ¼ºêµÈ ¾À
	map<wstring, shared_ptr<Scene>> m_scenes;	   // ¾À ¸®½ºÆ®
};