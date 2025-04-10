#pragma once
#include "GameAssetResourceTypes.h"


class GameAssetResources
{
public:
	GameAssetResources(const float& pixelsToUnits,
		const std::string& pathToResourceImages, 
		const std::string& pathToResourceFonts, 
		const std::string& pathToResourceAudios);
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



