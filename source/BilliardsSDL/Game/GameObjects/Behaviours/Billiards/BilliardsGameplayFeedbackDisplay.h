#pragma once
#include "../RendererExtras/FadingRenderer.h"
#include "../../../Audio/SFXSoundBuffer.h"


class BilliardsGameplayFeedbackDisplay
{
public:
	struct FadingTextsConfig
	{
	public:
		FadingRenderer* whiteBallEnterHole;
		FadingRenderer* blackBallEnterHole;
		FadingRenderer* wrongBallEnterHole;
		FadingRenderer* ballEnterHoleScore;
		FadingRenderer* ballEnterHoleScoreConsecutive;
		FadingRenderer* ballEnterHoleScoreLast;

		FadingRenderer* victoryHeader;
		FadingRenderer* victorySubHeader;
	};

	struct SoundsConfig
	{
	public:
		SoundsConfig(GameAudioManager* manager, 
			const SoundResourceData& penaltyResourceData,
			const SoundResourceData& lowPenaltyResourceData,
			const SoundResourceData& scorePointsResourceData,
			const SoundResourceData& playerChangeResourceData,
			const SoundResourceData& victoryResourceData
		);

	public:
		SFXSoundBuffer penaltySoundBuffer;
		SFXSoundBuffer lowPenaltySoundBuffer;
		SFXSoundBuffer scorePointsSoundBuffer;

		std::shared_ptr<SFXSound> playerChangeSound;
		std::shared_ptr<SFXSound> victorySound;
	};



public:
	BilliardsGameplayFeedbackDisplay(const FadingTextsConfig& fadingTexts, const SoundsConfig& sounds);

	void PlayWhiteBallEnterHole(const Vector2<float>& holeCenter);
	void PlayBlackBallEnterHole(const Vector2<float>& holeCenter);
	void PlayWrongBallEnterHole(const Vector2<float>& holeCenter, const Color& ballColor);
	void PlayBallEnterHoleScore(const Vector2<float>& holeCenter);
	void PlayBallEnterHoleScoreConsecutive(const Vector2<float>& holeCenter);
	void PlayBallEnterHoleScoreLast(const Vector2<float>& holeCenter);


	void PlayPlayerChange();
	void PlayVictory(const Color& winnerColor);


private:
	Vector2<float> HoleCenterToFadingPosition(const Vector2<float>& holeCenter);


private:
	FadingTextsConfig m_fadingTexts;
	SoundsConfig m_sounds;
};