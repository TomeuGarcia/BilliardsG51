#include "GameRenderFileData.h"

GameRenderFileData::GameRenderFileData(const int& defaultCameraShakeAmount)
	: m_cameraShakeAmount(defaultCameraShakeAmount)
{
}



int GameRenderFileData::GetCameraShakeAmount() const
{
	return m_cameraShakeAmount;
}

void GameRenderFileData::SetCameraShakeAmount(const int& cameraShakeAmount)
{
	m_cameraShakeAmount = cameraShakeAmount;
}



void GameRenderFileData::ReadAsBinary(std::ifstream& inputStream)
{
	BinaryUtilities::ReadInt(inputStream, m_cameraShakeAmount);
}

void GameRenderFileData::WriteAsBinary(std::ofstream& outputStream)
{
	BinaryUtilities::WriteInt(outputStream, m_cameraShakeAmount);
}
