#include "GameAssetResources.h"


GameAssetResources* GameAssetResources::s_instance = nullptr;

GameAssetResources::GameAssetResources(const float& pixelsToUnits,
	const std::string& pathToResourceImages, 
	const std::string& pathToResourceFonts, 
	const std::string& pathToResourceAudios)
	: 
	m_imageResources(pixelsToUnits, pathToResourceImages),
	m_textResources(pathToResourceFonts),
	m_audioResources(pathToResourceAudios)
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

const ImageResources& GameAssetResources::GetImage() const
{
	return m_imageResources;
}

const TextResources& GameAssetResources::GetText() const
{
	return m_textResources;
}

const AudioResources& GameAssetResources::GetAudio() const
{
	return m_audioResources;
}