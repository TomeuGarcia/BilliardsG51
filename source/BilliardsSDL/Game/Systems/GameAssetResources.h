#pragma once
#include "../Render/Renderers/Image/ImageResourceData.h"
#include "../Render/Renderers/Text/TextResourceData.h"
#include "../Audio/SoundResourceData.h"


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
	const ImageResourceData& GetDebugImageData();
	const ImageResourceData& GetDebugTransparentImageData();

	const ImageResourceData& GetWhiteBallImageData();
	const ImageResourceData& GetBlackBallImageData();
	const ImageResourceData& GetRedBallImageData();
	const ImageResourceData& GetBlueBallImageData();
	const ImageResourceData& GetRedStickImageData();
	const ImageResourceData& GetBlueStickImageData();
	const ImageResourceData& GetBoardImageData();

public:
	const TextResourceData& GetDebugTextFontData();

public:
	const SoundResourceData& GetBilliardBallHitOtherBallSoundData();
	const SoundResourceData& GetBilliardBallHitBoardSoundData();
	const SoundResourceData& GetButtonPressedSoundData();


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

private:
	TextResourceData m_debugTextFontData;

private:
	SoundResourceData m_billiardBallHitOtherBallSoundData;
	SoundResourceData m_billiardBallHitBoardSoundData;
	SoundResourceData m_buttonPressedSoundData;



private:
	static GameAssetResources* s_instance;
};