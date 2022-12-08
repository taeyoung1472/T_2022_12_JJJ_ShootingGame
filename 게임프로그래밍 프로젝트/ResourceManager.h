#pragma once
#include "pch.h"
#include "Sprite.h"
#include "PathManager.h"
#include "Object.h"

class ResourceManager
{
public:
	SINGLE(ResourceManager);

public:
	template<typename T>
	shared_ptr<T> Load(const wstring& name, const wstring path);

private:
	map<wstring, shared_ptr<Object>> m_resourceList;
};

template<typename T>
inline shared_ptr<T> ResourceManager::Load(const wstring& name, const wstring path)
{
	wstring fixedPath = PathManager::GetInst()->GetResourcePath();
	fixedPath += path;

	wstring extension = path.substr(path.rfind('.') + 1);

	auto findIt = m_resourceList.find(name);

	if (findIt == m_resourceList.end()) 
	{
		if (extension == L"bmp") {
			Sprite sprite;
			sprite.SetSprite(fixedPath);
			m_resourceList.insert({ name, make_shared<Sprite>(sprite) });
		}
	}

	return static_pointer_cast<T>(m_resourceList[name]);
}
