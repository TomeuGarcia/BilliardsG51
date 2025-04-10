#include "SingleSound.h"

SingleSound::SingleSound(Mix_Music* mixMusic)
	: m_mixMusic(mixMusic), m_channel(-1)
{
}

Mix_Music* SingleSound::GetMixMusic() const
{
	return m_mixMusic;
}

int SingleSound::GetChannel() const
{
	return m_channel;
}

void SingleSound::SetChannel(const int& channel)
{
	m_channel = channel;
}

void SingleSound::SetFinishedPlaying()
{
	m_channel = -1;
}

bool SingleSound::IsPlaying() const
{
	return m_channel != -1;
}
