#pragma once
#include "fmod.hpp"

enum class SOUND_CHANNEL
{
	BGM, EFFECT, FootStep, END
};

typedef struct tSoundInfo
{
	FMOD::Sound* pSound;
	bool isLoop;
}SOUNDINFO, * PSOUNDINFO;

class SoundManager
{
public:
	SINGLE(SoundManager);

private:
	SoundManager();
	~SoundManager();

public:
	void Update();

private:
	FMOD::System* m_pSystem;
	map<wstring, PSOUNDINFO> m_mapSod;
	FMOD::Channel* m_pChannel[(UINT)SOUND_CHANNEL::END];
	queue<wstring> m_playSoundStack;

public:
	void Init();
	void LoadSound(const wstring& _strKey, bool _bLoop, const wstring& _strRelativePath);
	void soundStackExcute(const wstring& _strKey);
	void Play(const wstring& _strKey);
	void Stop(SOUND_CHANNEL _eChannel);
	void Volume(SOUND_CHANNEL _eChannel, float _fVol);
	void Pause(SOUND_CHANNEL _eChannel, bool _p);
private:
	PSOUNDINFO FindSound(const wstring& _strKey);
};

