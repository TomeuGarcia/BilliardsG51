#pragma once
#include <filesystem>
#include "GameAssetResourceTypes.h"


class GameAssetResources
{
public:
	GameAssetResources(const float& pixelsToUnits,
		const std::filesystem::path& pathToResourceImages, 
		const std::filesystem::path& pathToResourceFonts,
		const std::filesystem::path& pathToResourceAudios);
	~GameAssetResources();

public:
	static GameAssetResources* GetInstance();


public:
	const ImageResources& GetImage() const;
	const TextResources& GetText() const;
	const AudioResources& GetAudio() const;


private:
	ImageResources m_imageResources;
	TextResources m_textResources;
	AudioResources m_audioResources;

private:
	static GameAssetResources* s_instance;
};



