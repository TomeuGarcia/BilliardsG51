#include "GameOptionsFileData.h"

GameOptionsFileData::GameOptionsFileData()
	:
	m_gameAudioFileData(100, 50, 50),
	m_gameRenderFileData(100)
{
}

GameAudioFileData& GameOptionsFileData::GetAudio()
{
	return m_gameAudioFileData;
}

GameRenderFileData& GameOptionsFileData::GetRender()
{
	return m_gameRenderFileData;
}

void GameOptionsFileData::ReadAsBinary(std::ifstream& inputStream)
{
	m_gameAudioFileData.ReadAsBinary(inputStream);
	m_gameRenderFileData.ReadAsBinary(inputStream);
}

void GameOptionsFileData::WriteAsBinary(std::ofstream& outputStream)
{
	m_gameAudioFileData.WriteAsBinary(outputStream);
	m_gameRenderFileData.WriteAsBinary(outputStream);
}
