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
	const ImageResourceData& GetDebugTransparentImageData();

	const ImageResourceData& GetWhiteBallImageData();
	const ImageResourceData& GetBlackBallImageData();
	const ImageResourceData& GetRedBallImageData();
	const ImageResourceData& GetBlueBallImageData();
	const ImageResourceData& GetRedStickImageData();
	const ImageResourceData& GetBlueStickImageData();
	const ImageResourceData& GetBoardImageData();

	const TextResourceData& GetDebugTextFontData();


private:
	ImageResourceData m_debugImageData;
	ImageResourceData m_debugTransparentImageData;

	ImageResourceData m_whiteBallImageData;
	ImageResourceData m_blackBallImageData;
	ImageResourceData m_redBallImageData;
	ImageResourceData m_blueBallImageData;
	ImageResourceData m_redStickImageData;
	ImageResourceData m_blueStickImageData;
	ImageResourceData m_boardImageData;

	TextResourceData m_debugTextFontData;

private:
	static GameAssetResources* s_instance;
};