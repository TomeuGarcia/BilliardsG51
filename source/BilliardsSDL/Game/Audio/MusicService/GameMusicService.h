#pragma once
#include <unordered_map>
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

public:
	GameMusicService();
	~GameMusicService();

	static GameMusicService* GetInstance();

public:
	void TransitionMusic(const MusicType& newMusicType);

private:
	void StopCurrentMusic();
	void PlayCurrentMusic();


private:
	std::unordered_map<MusicType, std::shared_ptr<MusicSound>> m_musicTypeToSound;
	MusicType m_currentMusicType;
	MusicSound* m_currentMusicSound;

private:
	static GameMusicService* s_instance;

};