#include "GameAssetResources.h"


GameAssetResources* GameAssetResources::s_instance = nullptr;

GameAssetResources::GameAssetResources(const std::string& pathToResources)
	: m_debugImageData(pathToResources + "Watcher_Unglitched_BossIcon.png", Vector2<int>(0, 0), Vector2<int>(3068, 3570))
{
	s_instance = this;
}

GameAssetResources::~GameAssetResources()
{
	s_instance = nullptr;
}



GameAssetResources* GameAssetResources::GetInstance()
{
	return s_instance;
}



const ImageResourceData& GameAssetResources::GetDebugImageData()
{
	return m_debugImageData;
}
