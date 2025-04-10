#pragma once
#include <SDL_mixer.h>


struct SingleSound
{
public:
	SingleSound(Mix_Music* mixMusic);

	Mix_Music* GetMixMusic() const;
	int GetChannel() const;

	void SetChannel(const int& channel);

	void SetFinishedPlaying();

	bool IsPlaying() const;


private:
	Mix_Music* m_mixMusic;
	int m_channel;
};