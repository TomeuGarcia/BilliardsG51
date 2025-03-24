#pragma once
#include "../Render/Renderers/Image/ImageResourceData.h"
#include "../Render/Renderers/Text/TextResourceData.h"


class GameAssetResources
{
public:
	GameAssetResources(const std::string& pathToResourceImages, 
					   const std::string& pathToResourceFonts, 
					   const std::string& pathToResourceAudios);
	~GameAssetResources();

public:
	static GameAssetResources* GetInstance();

public:
	const ImageResourceData& GetDebugImageData();
	const TextResourceData& GetDebugTextFontData();


private:
	ImageResourceData m_debugImageData;
	TextResourceData m_debugTextFontData;

private:
	static GameAssetResources* s_instance;
};