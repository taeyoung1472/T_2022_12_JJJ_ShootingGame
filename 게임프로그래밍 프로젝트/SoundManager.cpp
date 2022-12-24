#include "pch.h"
#include "SoundManager.h"
#include "PathManager.h"

SoundManager::SoundManager() : m_pSystem(nullptr)
{
}

SoundManager::~SoundManager()
{
	m_pSystem->close();
	m_pSystem->release();
}

void SoundManager::Update()
{
	if (!m_playSoundStack.empty()) 
	{
		soundStackExcute(m_playSoundStack.front());
		m_playSoundStack.pop();
	}
}

void SoundManager::Init()
{
	FMOD::System_Create(&m_pSystem);
	if (m_pSystem != nullptr)
		m_pSystem->init(10, FMOD_INIT_NORMAL, NULL);
}

void SoundManager::LoadSound(const wstring& _strKey, bool isLoop, const wstring& _strRelativePath)
{
	// 찾으면 생성 x
	if (FindSound(_strKey))
		return;
	wstring strFilePath = PathManager::GetInst()->GetResourcePath();
	strFilePath += _strRelativePath;
	// wstring to string
	string str;
	size_t size;
	str.resize(strFilePath.length());
	wcstombs_s(&size, &str[0], str.size() + 1, strFilePath.c_str(), strFilePath.size());
	// 루프 할지 말지 결정
	FMOD_MODE eMode = FMOD_LOOP_NORMAL; // 반복 출력
	if (!isLoop)
		eMode = FMOD_DEFAULT; // 사운드 1번만 출력
	PSOUNDINFO ptSound = new SOUNDINFO;
	ptSound->isLoop = isLoop;
	m_pSystem->createSound(str.c_str(), eMode, NULL, &ptSound->pSound);
	m_mapSod.insert({ _strKey,ptSound });
}

void SoundManager::soundStackExcute(const wstring& _strKey)
{
	PSOUNDINFO ptSound = FindSound(_strKey);
	if (!ptSound)
		return;
	m_pSystem->update();
	SOUND_CHANNEL eChannel = SOUND_CHANNEL::BGM;
	if (!ptSound->isLoop)
		eChannel = SOUND_CHANNEL::EFFECT;
	m_pSystem->playSound(ptSound->pSound, NULL, false, &m_pChannel[(UINT)eChannel]);
}

void SoundManager::Play(const wstring& _strKey)
{
	m_playSoundStack.push(_strKey);
}

void SoundManager::Stop(SOUND_CHANNEL _eChannel)
{
	m_pChannel[(UINT)_eChannel]->stop();
}

void SoundManager::Volume(SOUND_CHANNEL _eChannel, float _fVol)
{
	m_pChannel[(UINT)_eChannel]->setVolume(_fVol);
}

void SoundManager::Pause(SOUND_CHANNEL _eChannel, bool _p)
{
	m_pChannel[(UINT)_eChannel]->setPaused(_p);
}

PSOUNDINFO SoundManager::FindSound(const wstring& _strKey)
{
	map<wstring, PSOUNDINFO>::iterator iter = m_mapSod.find(_strKey);
	if (iter == m_mapSod.end())
		return nullptr;
	return iter->second;
}