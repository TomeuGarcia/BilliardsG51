#include "BilliardsGameplayFeedbackDisplay.h"

BilliardsGameplayFeedbackDisplay::BilliardsGameplayFeedbackDisplay()
	: m_fadingText_whiteBallEnterHole(nullptr)
{
}

void BilliardsGameplayFeedbackDisplay::Init(
	FadingRenderer* fadingText_whiteBallEnterHole,
	FadingRenderer* fadingText_blackBallEnterHole,
	FadingRenderer* fadingText_wrongBallEnterHole,
	FadingRenderer* fadingText_ballEnterHoleScore,
	FadingRenderer* fadingText_ballEnterHoleScoreConsecutive,
	FadingRenderer* fadingText_ballEnterHoleScoreLast)
{
	m_fadingText_whiteBallEnterHole = fadingText_whiteBallEnterHole;
	m_fadingText_blackBallEnterHole = fadingText_blackBallEnterHole;
	m_fadingText_wrongBallEnterHole = fadingText_wrongBallEnterHole;
	m_fadingText_ballEnterHoleScore = fadingText_ballEnterHoleScore;
	m_fadingText_ballEnterHoleScoreConsecutive = fadingText_ballEnterHoleScoreConsecutive;
	m_fadingText_ballEnterHoleScoreLast = fadingText_ballEnterHoleScoreLast;
}



void BilliardsGameplayFeedbackDisplay::PlayWhiteBallEnterHole(const Vector2<float>& holeCenter)
{
	m_fadingText_whiteBallEnterHole->StartShowing(HoleCenterToFadingPosition(holeCenter));
}

void BilliardsGameplayFeedbackDisplay::PlayBlackBallEnterHole(const Vector2<float>& holeCenter)
{
	m_fadingText_blackBallEnterHole->StartShowing(HoleCenterToFadingPosition(holeCenter));
}

void BilliardsGameplayFeedbackDisplay::PlayWrongBallEnterHole(const Vector2<float>& holeCenter, const Color& ballColor)
{
	m_fadingText_wrongBallEnterHole->SetStartingColor(ballColor);
	m_fadingText_wrongBallEnterHole->StartShowing(HoleCenterToFadingPosition(holeCenter));
}

void BilliardsGameplayFeedbackDisplay::PlayBallEnterHoleScore(const Vector2<float>& holeCenter)
{
	m_fadingText_ballEnterHoleScore->StartShowing(HoleCenterToFadingPosition(holeCenter));
}

void BilliardsGameplayFeedbackDisplay::PlayBallEnterHoleScoreConsecutive(const Vector2<float>& holeCenter)
{
	m_fadingText_ballEnterHoleScoreConsecutive->StartShowing(HoleCenterToFadingPosition(holeCenter));
}

void BilliardsGameplayFeedbackDisplay::PlayBallEnterHoleScoreLast(const Vector2<float>& holeCenter)
{
	m_fadingText_ballEnterHoleScoreLast->StartShowing(HoleCenterToFadingPosition(holeCenter));
}



Vector2<float> BilliardsGameplayFeedbackDisplay::HoleCenterToFadingPosition(const Vector2<float>& holeCenter)
{
	return holeCenter + (Vector2<float>::Up() * 0.2f);
}
