#pragma once
#include "../../../../Application/Systems/Files/Binary/IBinarySerializable.h"



class GameAudioFileData : public IBinarySerializable
{
public:
	GameAudioFileData(const int& defaultMasterVolume, const int& defaultMusicVolume, const int& defaultSFXVolume);

	int GetMasterVolume() const;
	int GetMusicVolume() const;
	int GetSFXVolume() const;

	void SetMasterVolume(const int& volume);
	void SetMusicVolume(const int& volume);
	void SetSFXVolume(const int& volume);

public:
	virtual void ReadAsBinary(std::ifstream& inputStream) override;
	virtual void WriteAsBinary(std::ofstream& outputStream) override;


private:
	int m_masterVolume;
	int m_musicVolume;
	int m_sfxVolume;
};