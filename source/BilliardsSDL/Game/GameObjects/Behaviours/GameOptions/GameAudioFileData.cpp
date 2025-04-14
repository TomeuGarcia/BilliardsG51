#include "GameAudioFileData.h"



GameAudioFileData::GameAudioFileData(const int& defaultMasterVolume, const int& defaultMusicVolume, const int& defaultSFXVolume)
	: m_masterVolume(defaultMasterVolume),
	m_musicVolume(defaultMusicVolume),
	m_sfxVolume(defaultSFXVolume)
{
}

int GameAudioFileData::GetMasterVolume() const
{
	return m_masterVolume;
}

int GameAudioFileData::GetMusicVolume() const
{
	return m_musicVolume;
}

int GameAudioFileData::GetSFXVolume() const
{
	return m_sfxVolume;
}


void GameAudioFileData::SetMasterVolume(const int& volume)
{
	m_masterVolume = volume;
}

void GameAudioFileData::SetMusicVolume(const int& volume)
{
	m_musicVolume = volume;
}

void GameAudioFileData::SetSFXVolume(const int& volume)
{
	m_sfxVolume = volume;
}



void GameAudioFileData::ReadAsBinary(std::ifstream& inputStream)
{
	BinaryUtilities::ReadInt(inputStream, m_masterVolume);
	BinaryUtilities::ReadInt(inputStream, m_musicVolume);
	BinaryUtilities::ReadInt(inputStream, m_sfxVolume);
}

void GameAudioFileData::WriteAsBinary(std::ofstream& outputStream)
{
	BinaryUtilities::WriteInt(outputStream, m_masterVolume);
	BinaryUtilities::WriteInt(outputStream, m_musicVolume);
	BinaryUtilities::WriteInt(outputStream, m_sfxVolume);
}
