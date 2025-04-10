#pragma once
#include <memory>
#include <set>

#include "IMusicSoundManager.h"
#include "MusicSound.h"

#include "ISFXSoundManager.h"
#include "SFXSound.h"


class GameAudioManager : public IMusicSoundManager, public ISFXSoundManager
{
public:
	GameAudioManager(AudioSystem* audioSystem);
	~GameAudioManager();

	static GameAudioManager* GetInstance();


public:
	std::shared_ptr<SFXSound> CreateSFXSound(const SoundResourceData& resourceData);
	std::shared_ptr<MusicSound> CreateMusicSound(const SoundResourceData& resourceData);

	void SetMasterVolume(const float& volume01);
	void SetMusicVolume(const float& volume01);
	void SetSFXVolume(const float& volume01);


public:
	virtual AudioSystem* GetAudioSystem() override;
	virtual float ComputeMusicEndVolume01(const float& baseVolume01) override;
	virtual float ComputeSFXEndVolume01(const float& baseVolume01) override;

	virtual void AddActiveMusicSound(MusicSound* musicSound) override;
	virtual void RemoveActiveMusicSound(MusicSound* musicSound) override;

	virtual void AddActiveSFXSound(SFXSound* sfxSound) override;
	virtual void RemoveActiveSFXSound(SFXSound* sfxSound) override;

	
private:
	void UpdateActiveSoundVolumes();


private:
	AudioSystem* m_audioSystem;

	float m_masterVolume01;
	float m_musicVolume01;
	float m_sfxVolume01;


private:
	static GameAudioManager* s_instance;

	std::set<MusicSound*> m_activeMusicSounds;
	std::set<SFXSound*> m_activeSFXSounds;
};