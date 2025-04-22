#pragma once
#include <SDL_mixer.h>

struct Sound
{
public:
	Sound(Mix_Chunk* mixChunk);

	Mix_Chunk* GetMixChunk() const;

	int GetChannel() const;
	void SetChannel(const int& channel);

	void SetFinishedPlaying();

	bool IsPlayingInChannel() const;


private:
	Mix_Chunk* m_mixChunk;
	int m_channel;
};