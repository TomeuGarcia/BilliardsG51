#include "GameAssetResources.h"


GameAssetResources* GameAssetResources::s_instance = nullptr;

GameAssetResources::GameAssetResources(const std::string& pathToResourceImages, 
									   const std::string& pathToResourceFonts, 
									   const std::string& pathToResourceAudios)	: 
	m_debugImageData(pathToResourceImages + "Watcher_Unglitched_BossIcon.png", Vector2<int>(0, 0), Vector2<int>(3068, 3570), false),
	m_debugTransparentImageData(pathToResourceImages + "ElectroWeb.png", Vector2<int>(0, 0), Vector2<int>(390, 390), false),
	m_debugTextFontData(pathToResourceFonts + "hinted-GWENT-ExtraBold.ttf")
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

const ImageResourceData& GameAssetResources::GetDebugTransparentImageData()
{
	return m_debugTransparentImageData;
}

const TextResourceData& GameAssetResources::GetDebugTextFontData()
{
	return m_debugTextFontData;
}
