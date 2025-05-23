#include "GameAssetResourceTypes.h"



ImageResources::ImageResources(const float& pixelsToUnits, const std::string& pathToResourceImages)
	:
	debugImageData(pathToResourceImages + "Watcher_Unglitched_BossIcon.png", Vector2<int>(0, 0), Vector2<int>(3068, 3570), false, pixelsToUnits),
	debugTransparentImageData(pathToResourceImages + "ElectroWeb.png", Vector2<int>(0, 0), Vector2<int>(390, 390), false, pixelsToUnits),
	debugPixelImageData(pathToResourceImages + "Pixel.png", Vector2<int>(0, 0), Vector2<int>(1, 1), true, pixelsToUnits),

	whiteBallImageData(pathToResourceImages + "BilliardsSprites.png", Vector2<int>(0, 0), Vector2<int>(32, 32), false, pixelsToUnits),
	blueBallImageData(pathToResourceImages + "BilliardsSprites.png", Vector2<int>(32, 0), Vector2<int>(32, 32), false, pixelsToUnits),
	redBallImageData(pathToResourceImages + "BilliardsSprites.png", Vector2<int>(64, 0), Vector2<int>(32, 32), false, pixelsToUnits),
	blackBallImageData(pathToResourceImages + "BilliardsSprites.png", Vector2<int>(96, 0), Vector2<int>(32, 32), false, pixelsToUnits),
	blueStickImageData(pathToResourceImages + "BilliardsSprites.png", Vector2<int>(132, 0), Vector2<int>(340, 13), false, pixelsToUnits),
	redStickImageData(pathToResourceImages + "BilliardsSprites.png", Vector2<int>(132, 17), Vector2<int>(340, 13), false, pixelsToUnits),
	boardImageData(pathToResourceImages + "BilliardsSprites.png", Vector2<int>(0, 32), Vector2<int>(1250, 702), false, pixelsToUnits)
{
}


TextResources::TextResources(const std::string& pathToResourceFonts)
	:
	defaultTextFontData(pathToResourceFonts + "Moviecal Regular.ttf"),
	titleTextFontData(pathToResourceFonts + "Movie Font.ttf"),
	popUpTextFontData(pathToResourceFonts + "ColateraSoft.ttf"),
	musicTextFontData(pathToResourceFonts + "PleaseWriteMeASong-70vV.ttf")
{
}


AudioResources::AudioResources(const std::string& pathToResourceAudios)
	:
	musicMainMenuSoundData(pathToResourceAudios + "Music/Scattle-Surfs_Up.mp3"),
	musicGameplaySoundData(pathToResourceAudios + "Music/Scattle-Generator.mp3"),

	buttonOkSoundData(pathToResourceAudios + "ButtonOk.wav"),
	buttonBackSoundData(pathToResourceAudios + "ButtonBack.wav"),
	buttonDangerSoundData(pathToResourceAudios + "ButtonDanger.wav"),
	textAppearSoundData(pathToResourceAudios + "TextAppear.wav"),

	gamePenaltySoundData(pathToResourceAudios + "Penalty.wav"),
	gameLowPenaltySoundData(pathToResourceAudios + "LowPenalty.wav"),
	gamePlayerChangeSoundData(pathToResourceAudios + "PlayerChange.wav"),
	gameScorePointsSoundData(pathToResourceAudios + "ScorePoints.wav"),
	gameVictorySoundData(pathToResourceAudios + "Victory.wav"),
	billiardBallHitOtherBallSoundData(pathToResourceAudios + "BilliardBallHitOtherBall.wav"),
	billiardBallHitBoardSoundData(pathToResourceAudios + "BilliardBallHitWood.wav"),
	billiardBallMovedSoundData(pathToResourceAudios + "BilliardBallMoved.wav")
{
}
