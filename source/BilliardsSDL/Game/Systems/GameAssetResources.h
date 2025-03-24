#pragma once
#include "../Render/Renderers/ImageResourceData.h"


class GameAssetResources
{
public:
	GameAssetResources(const std::string& pathToResources);
	~GameAssetResources();

public:
	static GameAssetResources* GetInstance();

public:
	const ImageResourceData& GetDebugImageData();



private:
	ImageResourceData m_debugImageData;

private:
	static GameAssetResources* s_instance;
};