#include "GameAssetResources.h"


GameAssetResources* GameAssetResources::s_instance = nullptr;

GameAssetResources::GameAssetResources(const float& pixelsToUnits,
	const std::filesystem::path& pathToResourceImages,
	const std::filesystem::path& pathToResourceFonts,
	const std::filesystem::path& pathToResourceAudios)
	: 
	m_imageResources(pixelsToUnits, pathToResourceImages.string()),
	m_textResources(pathToResourceFonts.string()),
	m_audioResources(pathToResourceAudios.string())
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