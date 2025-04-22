#pragma once
#include "../../../../../Application/Systems/Files/Binary/IBinarySerializable.h"



class GameRenderFileData : public IBinarySerializable
{
public:
	GameRenderFileData(const int& defaultCameraShakeAmount);

	int GetCameraShakeAmount() const;

	void SetCameraShakeAmount(const int& cameraShakeAmount);

public:
	virtual void ReadAsBinary(std::ifstream& inputStream) override;
	virtual void WriteAsBinary(std::ofstream& outputStream) override;


private:
	int m_cameraShakeAmount;
};