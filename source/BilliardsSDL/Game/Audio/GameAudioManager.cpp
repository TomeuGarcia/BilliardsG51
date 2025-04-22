#include "GameAudioManager.h"


GameAudioManager* GameAudioManager::s_instance = nullptr;



GameAudioManager::GameAudioManager(AudioSystem* audioSystem)
	: m_audioSystem(audioSystem),
	m_masterVolume01(1.0f),
	m_musicVolume01(0.5f),
	m_sfxVolume01(0.5f)
{
	s_instance = this;
}

GameAudioManager::~GameAudioManager()
{
	s_instance = nullptr;
}



GameAudioManager* GameAudioManager::GetInstance()
{
	return s_instance;
}



std::shared_ptr<SFXSound> GameAudioManager::CreateSFXSound(const SoundResourceData& resourceData)
{
	return std::make_shared<SFXSound>(this, resourceData);
}

std::shared_ptr<MusicSound> GameAudioManager::CreateMusicSound(const SoundResourceData& resourceData)
{
	return std::make_shared<MusicSound>(this, resourceData);
}



float GameAudioManager::GetMasterVolume01() const
{
	return m_masterVolume01;
}

float GameAudioManager::GetMusicVolume01() const
{
	return m_musicVolume01;
}

float GameAudioManager::GetSFXVolume01() const
{
	return m_sfxVolume01;
}


void GameAudioManager::SetMasterVolume(const float& volume01)
{
	m_masterVolume01 = Math::Clamp01(volume01);
	UpdateActiveSoundVolumes();
}

void GameAudioManager::SetMusicVolume(const float& volume01)
{
	m_musicVolume01 = Math::Clamp01(volume01);
	UpdateActiveSoundVolumes();
}

void GameAudioManager::SetSFXVolume(const float& volume01)
{
	m_sfxVolume01 = Math::Clamp01(volume01);
	UpdateActiveSoundVolumes();
}





AudioSystem* GameAudioManager::GetAudioSystem()
{
	return m_audioSystem;
}

float GameAudioManager::ComputeSFXEndVolume01(const float& baseVolume01)
{
	return m_masterVolume01 * m_sfxVolume01 * baseVolume01;
}

float GameAudioManager::ComputeMusicEndVolume01(const float& baseVolume01)
{
	return m_masterVolume01 * m_musicVolume01 * baseVolume01;
}



void GameAudioManager::AddActiveMusicSound(MusicSound* musicSound)
{
	m_activeMusicSounds.insert(musicSound);
}

void GameAudioManager::RemoveActiveMusicSound(MusicSound* musicSound)
{
	m_activeMusicSounds.erase(musicSound);
}



void GameAudioManager::AddActiveSFXSound(SFXSound* sfxSound)
{
	m_activeSFXSounds.insert(sfxSound);
}

void GameAudioManager::RemoveActiveSFXSound(SFXSound* sfxSound)
{
	m_activeSFXSounds.erase(sfxSound);
}



void GameAudioManager::UpdateActiveSoundVolumes()
{
	for (auto it = m_activeMusicSounds.begin(); it != m_activeMusicSounds.end(); ++it)
	{
		(*it)->RefreshVolume();
	}

	for (auto it = m_activeSFXSounds.begin(); it != m_activeSFXSounds.end(); ++it)
	{
		(*it)->RefreshVolume();
	}
}


