#include "GameMusicService.h"


GameMusicService* GameMusicService::s_instance = nullptr;

GameMusicService::GameMusicService()
	: m_musicTypeToSound(), m_currentMusicType(MusicType::None), m_currentMusicSound(nullptr)
{
	m_musicTypeToSound[MusicType::MainMenu] = GameAudioManager::GetInstance()->CreateMusicSound(
		GameAssetResources::GetInstance()->GetAudio().musicMainMenuSoundData);
	m_musicTypeToSound[MusicType::Gameplay] = GameAudioManager::GetInstance()->CreateMusicSound(
		GameAssetResources::GetInstance()->GetAudio().musicGameplaySoundData);

	s_instance = this;
}

GameMusicService::~GameMusicService()
{	
	StopCurrentMusic();

	s_instance = nullptr;
}


GameMusicService* GameMusicService::GetInstance()
{
	return s_instance;
}



void GameMusicService::TransitionMusic(const MusicType& newMusicType)
{
	if (newMusicType == MusicType::None)
	{
		StopCurrentMusic();
		return;
	}
	else if (m_currentMusicType != newMusicType)
	{
		StopCurrentMusic();
		m_currentMusicType = newMusicType;
		PlayCurrentMusic();
	}
}

void GameMusicService::StopCurrentMusic()
{
	if (m_currentMusicSound != nullptr)
	{
		m_currentMusicSound->Stop();
	}
}

void GameMusicService::PlayCurrentMusic()
{
	m_currentMusicSound = m_musicTypeToSound[m_currentMusicType].get();
	m_currentMusicSound->Play();
}
