#pragma once
#include "ISFXSoundManager.h"
#include "SoundResourceData.h"


class SFXSound
{
public:
	SFXSound(ISFXSoundManager* manager, const SoundResourceData& resourceData);
	~SFXSound();

	void Play();
	void Stop();
	void Pause();
	void Resume();

	void SetVolume(const float& volume01);

	void RefreshVolume();


private:
	inline AudioSystem* GetAudioSystem() const;


private:
	ISFXSoundManager* m_manager;
	Sound m_sound;

	float m_volume01;
};