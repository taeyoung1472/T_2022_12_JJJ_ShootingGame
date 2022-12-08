#pragma once
class PathManager
{
public:
	SINGLE(PathManager);

private:
	PathManager();
	~PathManager();

public:
	void Init();
	const wchar_t* GetResourcePath() {
		return m_ResourcePath;
	}

private:
	wchar_t m_ResourcePath[255];
};

