#pragma once
#include <unordered_map>
#include <string>
#include "../GameAudioManager.h"
#include "../../Systems/GameAssetResources.h"


class GameMusicService
{
public:
	enum class MusicType
	{
		None,
		MainMenu,
		Gameplay
	};

private:
	struct MusicData
	{
		std::shared_ptr<MusicSound> musicSound;
		std::string authorAndName;
	};


public:
	GameMusicService();
	~GameMusicService();

	static GameMusicService* GetInstance();

public:
	std::string_view GetMusicAuthorAndName(const MusicType& musicType);
	bool IsMusicPlaying(const MusicType& musicType);
	bool TransitionMusic(const MusicType& newMusicType);

private:
	void StopCurrentMusic();
	void PlayCurrentMusic();


private:
	std::unordered_map<MusicType, MusicData> m_musicTypeToSound;
	MusicType m_currentMusicType;
	MusicData* m_currentMusic;

private:
	static GameMusicService* s_instance;

};