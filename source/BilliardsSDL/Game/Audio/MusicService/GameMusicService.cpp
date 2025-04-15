#include "GameMusicService.h"


GameMusicService* GameMusicService::s_instance = nullptr;

GameMusicService::GameMusicService()
	: m_musicTypeToSound(), m_currentMusicType(MusicType::None), m_currentMusic(nullptr)
{
	m_musicTypeToSound[MusicType::MainMenu] = MusicData{
		GameAudioManager::GetInstance()->CreateMusicSound(GameAssetResources::GetInstance()->GetAudio().musicMainMenuSoundData),
		std::string("Scattle : Surf\'s Up")
	};
	m_musicTypeToSound[MusicType::Gameplay] = MusicData{
		GameAudioManager::GetInstance()->CreateMusicSound(GameAssetResources::GetInstance()->GetAudio().musicGameplaySoundData),
		std::string("Scattle : Generator")
	};

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



std::string_view GameMusicService::GetMusicAuthorAndName(const MusicType& musicType)
{
	auto it = m_musicTypeToSound.find(musicType);
	if (it != m_musicTypeToSound.end())
	{
		return it->second.authorAndName;
	}

	return std::string_view();
}

bool GameMusicService::IsMusicPlaying(const MusicType& musicType)
{
	return m_currentMusicType == musicType;
}

bool GameMusicService::TransitionMusic(const MusicType& newMusicType)
{
	if (newMusicType == MusicType::None)
	{
		StopCurrentMusic();
		return false;
	}
	else if (!IsMusicPlaying(newMusicType))
	{
		StopCurrentMusic();
		m_currentMusicType = newMusicType;
		PlayCurrentMusic();
		return true;
	}

	return false;
}

void GameMusicService::StopCurrentMusic()
{
	if (m_currentMusic != nullptr)
	{
		m_currentMusic->musicSound->Stop();
	}
}

void GameMusicService::PlayCurrentMusic()
{
	m_currentMusic = &m_musicTypeToSound[m_currentMusicType];
	m_currentMusic->musicSound->Play();
}
