#pragma once
#include "FileData/GameOptionsFileData.h"
#include "../../../../Application/Systems/Files/Binary/BinaryFile.h"

#include "../../../Systems/GameFileResources.h"

#include "../../../Audio/GameAudioManager.h"
#include "../../../Render/GameRenderManager.h"



class GameOptionsManager
{
public:
	GameOptionsManager();

	void Load();
	void Save();

	const GameAudioFileData& GetGameAudioData();
	const GameRenderFileData& GetGameRenderData();

private:
	const float To01(const int& value100);
	const int To100(const float& value01);


private:
	BinaryFile m_optionsFile;
	GameOptionsFileData m_gameOptionsFileData;
};