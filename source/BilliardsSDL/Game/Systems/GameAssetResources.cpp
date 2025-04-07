#include "GameAssetResources.h"


GameAssetResources* GameAssetResources::s_instance = nullptr;

GameAssetResources::GameAssetResources(const float& pixelsToUnits,
	const std::string& pathToResourceImages, 
	const std::string& pathToResourceFonts, 
	const std::string& pathToResourceAudios)
	: 
	m_debugImageData(pathToResourceImages + "Watcher_Unglitched_BossIcon.png", Vector2<int>(0, 0), Vector2<int>(3068, 3570), false, pixelsToUnits),
	m_debugTransparentImageData(pathToResourceImages + "ElectroWeb.png", Vector2<int>(0, 0), Vector2<int>(390, 390), false, pixelsToUnits),

	m_whiteBallImageData(pathToResourceImages + "BilliardsSprites.png", Vector2<int>(0, 0), Vector2<int>(32, 32), false, pixelsToUnits),
	m_blueBallImageData(pathToResourceImages + "BilliardsSprites.png",	Vector2<int>(32, 0), Vector2<int>(32, 32), false, pixelsToUnits),
	m_redBallImageData(pathToResourceImages + "BilliardsSprites.png",	Vector2<int>(64, 0), Vector2<int>(32, 32), false, pixelsToUnits),
	m_blackBallImageData(pathToResourceImages + "BilliardsSprites.png", Vector2<int>(96, 0), Vector2<int>(32, 32), false, pixelsToUnits),
	m_blueStickImageData(pathToResourceImages + "BilliardsSprites.png",	Vector2<int>(132, 0), Vector2<int>(340, 12), false, pixelsToUnits),
	m_redStickImageData(pathToResourceImages + "BilliardsSprites.png",	Vector2<int>(132, 17), Vector2<int>(340, 12), false, pixelsToUnits),
	m_boardImageData(pathToResourceImages + "BilliardsSprites.png",		Vector2<int>(0, 32), Vector2<int>(1250, 702), false, pixelsToUnits),

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

const ImageResourceData& GameAssetResources::GetWhiteBallImageData()
{
	return m_whiteBallImageData;
}

const ImageResourceData& GameAssetResources::GetBlackBallImageData()
{
	return m_blackBallImageData;
}

const ImageResourceData& GameAssetResources::GetRedBallImageData()
{
	return m_redBallImageData;
}

const ImageResourceData& GameAssetResources::GetBlueBallImageData()
{
	return m_blueBallImageData;
}

const ImageResourceData& GameAssetResources::GetRedStickImageData()
{
	return m_redStickImageData;
}

const ImageResourceData& GameAssetResources::GetBlueStickImageData()
{
	return m_blueStickImageData;
}

const ImageResourceData& GameAssetResources::GetBoardImageData()
{
	return m_boardImageData;
}

const TextResourceData& GameAssetResources::GetDebugTextFontData()
{
	return m_debugTextFontData;
}
