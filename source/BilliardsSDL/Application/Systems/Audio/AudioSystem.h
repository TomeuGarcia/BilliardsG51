#pragma once
#include <SDL_mixer.h>
#include <string>
#include <memory>
#include <map>

#include "Sound.h"
#include "SingleSound.h"

#include "../../../Shared/Math/Math.h"


class AudioSystem
{
public:
	AudioSystem();

	void Init();
	void Cleanup();


	Sound LoadWAVSound(const std::string& completePath);
	void DeleteSound(const Sound& sound);
	void PlaySound(Sound& sound, const float& volume01);
	void StopSound(const Sound& sound);
	void PauseSound(const Sound& sound);
	void ResumeSound(const Sound& sound);
	void SetSoundVolume(const Sound& sound, const float& volume01);

	SingleSound LoadSingleSound(const std::string& completePath);
	void DeleteSingleSound(const SingleSound& singleSound);
	void PlaySingleSound(SingleSound& singleSound, const float& volume01, const int& loops);
	void StopSingleSound(const SingleSound& singleSound);
	void PauseSingleSound(const SingleSound& singleSound);
	void ResumeSingleSound(const SingleSound& singleSound);
	void SetSingleSoundVolume(const SingleSound& singleSound, const float& volume01);


private:
	int Volume01To255(const float& volume01);


private:
	static void OnChannelFinished(int channel);
	static void OnMusicFinished();

	static void AddPlayingSound(Sound* sound, const int& channel);
	static void RemovePlayingSound(const int& channel);

	static void SetPlayingSingleSound(SingleSound* singleSound);
	static void RemovePlayingSingleSound();

private:
	static std::map<int, Sound*> s_currentlyPlayingChannelsToSounds;
	static SingleSound* s_currentlyPlayingSingleSound;
};