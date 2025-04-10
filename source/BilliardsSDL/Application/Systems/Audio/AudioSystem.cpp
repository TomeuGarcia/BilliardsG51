#include "AudioSystem.h"



std::map<int, Sound*> AudioSystem::s_currentlyPlayingChannelsToSounds{};
SingleSound* AudioSystem::s_currentlyPlayingSingleSound = nullptr;



AudioSystem::AudioSystem()
{
}

void AudioSystem::Init()
{
	const int numberOfChannels = MIX_DEFAULT_CHANNELS;
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_S16, numberOfChannels, 4096);

	Mix_ChannelFinished(AudioSystem::OnChannelFinished);
	Mix_HookMusicFinished(AudioSystem::OnMusicFinished);
}

void AudioSystem::Cleanup()
{
	Mix_ChannelFinished(NULL);
	Mix_HookMusicFinished(NULL);

	Mix_CloseAudio();	
}



Sound AudioSystem::LoadWAVSound(const std::string& completePath)
{
	Mix_Chunk* mixChunk = Mix_LoadWAV(completePath.c_str());
	return Sound{ mixChunk };
}

void AudioSystem::DeleteSound(const Sound& sound)
{	
	if (sound.IsPlayingInChannel())
	{
		Mix_HaltChannel(sound.GetChannel());
	}

	Mix_FreeChunk(sound.GetMixChunk());
}

void AudioSystem::PlaySound(Sound& sound, const float& volume01)
{
	const int channel = Mix_PlayChannel(-1, sound.GetMixChunk(), 0);
	
	if (channel == -1)
	{
		//std::printf("%s\n", SDL_GetError());
	}
	else
	{
		sound.SetChannel(channel);
		SetSoundVolume(sound, volume01);
		AudioSystem::AddPlayingSound(&sound, channel);
	}
}

void AudioSystem::StopSound(const Sound& sound)
{
	if (sound.IsPlayingInChannel())
	{
		Mix_HaltChannel(sound.GetChannel());	
	}
}

void AudioSystem::PauseSound(const Sound& sound)
{
	if (sound.IsPlayingInChannel())
	{
		Mix_Pause(sound.GetChannel());
	}
}

void AudioSystem::ResumeSound(const Sound& sound)
{
	if (sound.IsPlayingInChannel())
	{
		Mix_Resume(sound.GetChannel());
	}
}

void AudioSystem::SetSoundVolume(const Sound& sound, const float& volume01)
{
	if (sound.IsPlayingInChannel())
	{
		Mix_VolumeChunk(sound.GetMixChunk(), Volume01To255(volume01));
	}
}



SingleSound AudioSystem::LoadSingleSound(const std::string& completePath)
{
	Mix_Music* mixChunk = Mix_LoadMUS(completePath.c_str());
	return SingleSound{ mixChunk };
}

void AudioSystem::DeleteSingleSound(const SingleSound& singleSound)
{
	if (singleSound.IsPlaying())
	{
		Mix_HaltMusic();
	}

	Mix_FreeMusic(singleSound.GetMixMusic());
}

void AudioSystem::PlaySingleSound(SingleSound& singleSound, const float& volume01, const int& loops)
{
	const int channel = Mix_PlayMusic(singleSound.GetMixMusic(), loops);

	if (channel == -1)
	{
		//std::printf("%s\n", SDL_GetError());
	}
	else
	{
		SetSingleSoundVolume(singleSound, volume01);
		AudioSystem::SetPlayingSingleSound(&singleSound);
	}
}

void AudioSystem::StopSingleSound(const SingleSound& singleSound)
{
	if (singleSound.IsPlaying())
	{
		Mix_HaltMusic();
	}
}

void AudioSystem::PauseSingleSound(const SingleSound& singleSound)
{
	if (singleSound.IsPlaying())
	{
		Mix_PauseMusic();
	}
}

void AudioSystem::ResumeSingleSound(const SingleSound& singleSound)
{
	if (singleSound.IsPlaying())
	{
		Mix_PauseMusic();
	}
}

void AudioSystem::SetSingleSoundVolume(const SingleSound& singleSound, const float& volume01)
{
	if (singleSound.IsPlaying())
	{
		Mix_VolumeMusic(Volume01To255(volume01));
	}
}




int AudioSystem::Volume01To255(const float& volume01)
{
	return Math::Clamp01(volume01) * 255;
}



void AudioSystem::OnChannelFinished(int channel)
{
	AudioSystem::RemovePlayingSound(channel);
}

void AudioSystem::OnMusicFinished()
{
	AudioSystem::RemovePlayingSingleSound();
}



void AudioSystem::AddPlayingSound(Sound* sound, const int& channel)
{
	AudioSystem::s_currentlyPlayingChannelsToSounds[channel] = sound;
}

void AudioSystem::RemovePlayingSound(const int& channel)
{
	AudioSystem::s_currentlyPlayingChannelsToSounds[channel]->SetFinishedPlaying();
	AudioSystem::s_currentlyPlayingChannelsToSounds.erase(channel);
}



void AudioSystem::SetPlayingSingleSound(SingleSound* singleSound)
{
	AudioSystem::s_currentlyPlayingSingleSound = singleSound;
}

void AudioSystem::RemovePlayingSingleSound()
{
	AudioSystem::s_currentlyPlayingSingleSound->SetFinishedPlaying();
	AudioSystem::s_currentlyPlayingSingleSound = nullptr;
}
