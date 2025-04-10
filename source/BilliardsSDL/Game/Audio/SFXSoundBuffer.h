#pragma once
#include <vector>
#include "GameAudioManager.h"
#include "SFXSound.h"



class SFXSoundBuffer
{
public:
	SFXSoundBuffer(GameAudioManager* manager, const SoundResourceData& resourceData, const int& bufferCount);


	void PlayNext();
	void PlayNextWithVolume(const float& volume01);
	void SetVolumeToAll(const float& volume01);


private:
	std::vector<std::shared_ptr<SFXSound>> m_sfxSounds;
	int m_nextSoundIndex;
};