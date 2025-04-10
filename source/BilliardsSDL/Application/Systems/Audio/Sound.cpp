#include "Sound.h"



Sound::Sound(Mix_Chunk* mixChunk)
	: m_mixChunk(mixChunk), m_channel(-1)
{
}

Mix_Chunk* Sound::GetMixChunk() const
{
	return m_mixChunk;
}


int Sound::GetChannel() const
{
	return m_channel;
}

void Sound::SetChannel(const int& channel)
{
	m_channel = channel;
}

void Sound::SetFinishedPlaying()
{
	m_channel = -1;
}


bool Sound::IsPlayingInChannel() const
{
	return m_channel != -1;
}