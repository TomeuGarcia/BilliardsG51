#pragma once
#include "../Render/Renderers/Image/ImageResourceData.h"
#include "../Render/Renderers/Text/TextResourceData.h"
#include "../Audio/SoundResourceData.h"


struct ImageResources
{
public:
	ImageResources(const float& pixelsToUnits, const std::string& pathToResourceImages);

public:
	ImageResourceData debugImageData;
	ImageResourceData debugTransparentImageData;

	ImageResourceData whiteBallImageData;
	ImageResourceData blackBallImageData;
	ImageResourceData redBallImageData;
	ImageResourceData blueBallImageData;
	ImageResourceData redStickImageData;
	ImageResourceData blueStickImageData;
	ImageResourceData boardImageData;
};



struct TextResources
{
public:
	TextResources(const std::string& pathToResourceFonts);

public:
	TextResourceData debugTextFontData;
};



struct AudioResources
{
public:
	AudioResources(const std::string& pathToResourceAudios);

public:
	SoundResourceData buttonOkSoundData;
	SoundResourceData buttonBackSoundData;
	SoundResourceData textAppearSoundData;

	SoundResourceData gamePenaltySoundData;
	SoundResourceData gameLowPenaltySoundData;
	SoundResourceData gamePlayerChangeSoundData;
	SoundResourceData gameScorePointsSoundData;
	SoundResourceData gameVictorySoundData;

	SoundResourceData billiardBallHitOtherBallSoundData;
	SoundResourceData billiardBallHitBoardSoundData;
	SoundResourceData billiardBallMovedSoundData;
};