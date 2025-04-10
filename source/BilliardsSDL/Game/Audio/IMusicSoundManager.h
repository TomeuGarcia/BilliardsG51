#pragma once
#include "../../Application/Systems/Audio/AudioSystem.h"


class MusicSound;

class IMusicSoundManager
{
public:
	virtual AudioSystem* GetAudioSystem() = 0;
	virtual float ComputeMusicEndVolume01(const float& baseVolume01) = 0;

	virtual void AddActiveMusicSound(MusicSound* musicSound) = 0;
	virtual void RemoveActiveMusicSound(MusicSound* musicSound) = 0;
};