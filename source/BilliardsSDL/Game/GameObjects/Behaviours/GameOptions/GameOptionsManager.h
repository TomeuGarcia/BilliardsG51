#pragma once
#include "GameAudioFileData.h"
#include "../../../../Application/Systems/Files/Binary/BinaryFile.h"

#include "../../../Systems/GameFileResources.h"

#include "../../../Audio/GameAudioManager.h"



class GameOptionsManager
{
public:
	GameOptionsManager();

	void Load();
	void Save();

	const GameAudioFileData& GetGameAudioData();

private:
	const float ToVolume01(const int& volume100);
	const int ToVolume100(const float& volume01);


private:
	BinaryFile m_optionsFile;
	GameAudioFileData m_gameAudioFileData;
};