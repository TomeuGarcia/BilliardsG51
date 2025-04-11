#include "BilliardsGameplayFeedbackDisplay.h"



BilliardsGameplayFeedbackDisplay::SoundsConfig::SoundsConfig(GameAudioManager* manager, 
	const SoundResourceData& penaltyResourceData, 
	const SoundResourceData& lowPenaltyResourceData,
	const SoundResourceData& scorePointsResourceData, 
	const SoundResourceData& playerChangeResourceData,
	const SoundResourceData& victoryResourceData) 
	:
	penaltySoundBuffer(manager, penaltyResourceData, 2),
	lowPenaltySoundBuffer(manager, lowPenaltyResourceData, 2),
	scorePointsSoundBuffer(manager, scorePointsResourceData, 2),
	playerChangeSound(std::make_shared<SFXSound>(manager, playerChangeResourceData)),
	victorySound(std::make_shared<SFXSound>(manager, victoryResourceData))
{
}




BilliardsGameplayFeedbackDisplay::BilliardsGameplayFeedbackDisplay(const FadingTextsConfig& fadingTexts, const SoundsConfig& sounds)
	: m_fadingTexts(fadingTexts), m_sounds(sounds)
{
	m_fadingTexts.victoryHeader->GetGameObject()->SetActive(false);
	m_fadingTexts.victorySubHeader->GetGameObject()->SetActive(false);
}


void BilliardsGameplayFeedbackDisplay::PlayWhiteBallEnterHole(const Vector2<float>& holeCenter)
{
	m_fadingTexts.whiteBallEnterHole->StartShowing(HoleCenterToFadingPosition(holeCenter));	
	m_sounds.penaltySoundBuffer.PlayNext();
}

void BilliardsGameplayFeedbackDisplay::PlayBlackBallEnterHole(const Vector2<float>& holeCenter)
{
	m_fadingTexts.blackBallEnterHole->StartShowing(HoleCenterToFadingPosition(holeCenter));
	m_sounds.penaltySoundBuffer.PlayNext();
}

void BilliardsGameplayFeedbackDisplay::PlayWrongBallEnterHole(const Vector2<float>& holeCenter, const Color& ballColor)
{
	m_fadingTexts.wrongBallEnterHole->SetStartingColor(ballColor);
	m_fadingTexts.wrongBallEnterHole->StartShowing(HoleCenterToFadingPosition(holeCenter));
	m_sounds.lowPenaltySoundBuffer.PlayNext();
}

void BilliardsGameplayFeedbackDisplay::PlayBallEnterHoleScore(const Vector2<float>& holeCenter)
{
	m_fadingTexts.ballEnterHoleScore->StartShowing(HoleCenterToFadingPosition(holeCenter));
	m_sounds.scorePointsSoundBuffer.PlayNext();
}

void BilliardsGameplayFeedbackDisplay::PlayBallEnterHoleScoreConsecutive(const Vector2<float>& holeCenter)
{
	m_fadingTexts.ballEnterHoleScoreConsecutive->StartShowing(HoleCenterToFadingPosition(holeCenter));
	m_sounds.scorePointsSoundBuffer.PlayNext();
}

void BilliardsGameplayFeedbackDisplay::PlayBallEnterHoleScoreLast(const Vector2<float>& holeCenter)
{
	m_fadingTexts.ballEnterHoleScoreLast->StartShowing(HoleCenterToFadingPosition(holeCenter));
	m_sounds.scorePointsSoundBuffer.PlayNext();
}



void BilliardsGameplayFeedbackDisplay::PlayPlayerChange()
{
	m_sounds.playerChangeSound->Play();
}

void BilliardsGameplayFeedbackDisplay::PlayVictory(const Color& winnerColor)
{
	m_fadingTexts.victoryHeader->GetGameObject()->SetActive(true);
	m_fadingTexts.victorySubHeader->GetGameObject()->SetActive(true);

	m_fadingTexts.victoryHeader->SetStartingColor(winnerColor.WithAlpha(0));
	m_fadingTexts.victoryHeader->StartShowing(Vector2<float>(0.0f, 0.25f));

	m_fadingTexts.victorySubHeader->StartShowingWithDelay(Vector2<float>(0.0f, -1.0f), 0.15f);

	m_sounds.victorySound->Play();
}



Vector2<float> BilliardsGameplayFeedbackDisplay::HoleCenterToFadingPosition(const Vector2<float>& holeCenter)
{
	return holeCenter + (Vector2<float>::Up() * 0.2f);
}

