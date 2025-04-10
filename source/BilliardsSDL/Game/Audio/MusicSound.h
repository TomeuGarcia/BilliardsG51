#pragma once
#include "IMusicSoundManager.h"
#include "SoundResourceData.h"


class MusicSound
{
public:
	MusicSound(IMusicSoundManager* manager, const SoundResourceData& resourceData);
	~MusicSound();

	void Play();
	void Stop();
	void Pause();
	void Resume();

	void SetLoops(const int& loops);
	void SetVolume(const float& volume01);

	void RefreshVolume();


private:
	inline AudioSystem* GetAudioSystem() const;


private:
	IMusicSoundManager* m_manager;
	SingleSound m_singleSound;

	float m_volume01;
	int m_loops;
};
