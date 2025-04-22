#pragma once
#include "../../../../../Application/Systems/Files/Binary/IBinarySerializable.h"

#include "GameAudioFileData.h"
#include "GameRenderFileData.h"



class GameOptionsFileData : public IBinarySerializable
{
public:
	GameOptionsFileData();

	GameAudioFileData& GetAudio();
	GameRenderFileData& GetRender();

public:
	virtual void ReadAsBinary(std::ifstream& inputStream) override;
	virtual void WriteAsBinary(std::ofstream& outputStream) override;


private:
	GameAudioFileData m_gameAudioFileData;
	GameRenderFileData m_gameRenderFileData;
};