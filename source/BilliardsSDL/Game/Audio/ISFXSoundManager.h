#pragma once
#include "../../Application/Systems/Audio/AudioSystem.h"


class SFXSound;

class ISFXSoundManager
{
public:
	virtual AudioSystem* GetAudioSystem() = 0;
	virtual float ComputeSFXEndVolume01(const float& baseVolume01) = 0;

	virtual void AddActiveSFXSound(SFXSound* sfxSound) = 0;
	virtual void RemoveActiveSFXSound(SFXSound* sfxSound) = 0;
};