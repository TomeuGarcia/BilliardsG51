#pragma once
#include "../RendererExtras/FadingRenderer.h"


class BilliardsGameplayFeedbackDisplay
{
public:
	BilliardsGameplayFeedbackDisplay();

	void Init(FadingRenderer* fadingText_whiteBallEnterHole,
		FadingRenderer* fadingText_blackBallEnterHole,
		FadingRenderer* fadingText_wrongBallEnterHole,
		FadingRenderer* fadingText_ballEnterHoleScore,
		FadingRenderer* fadingText_ballEnterHoleScoreConsecutive,
		FadingRenderer* fadingText_ballEnterHoleScoreLast);


	void PlayWhiteBallEnterHole(const Vector2<float>& holeCenter);
	void PlayBlackBallEnterHole(const Vector2<float>& holeCenter);
	void PlayWrongBallEnterHole(const Vector2<float>& holeCenter, const Color& ballColor);
	void PlayBallEnterHoleScore(const Vector2<float>& holeCenter);
	void PlayBallEnterHoleScoreConsecutive(const Vector2<float>& holeCenter);
	void PlayBallEnterHoleScoreLast(const Vector2<float>& holeCenter);


private:
	Vector2<float> HoleCenterToFadingPosition(const Vector2<float>& holeCenter);


private:
	FadingRenderer* m_fadingText_whiteBallEnterHole;
	FadingRenderer* m_fadingText_blackBallEnterHole;
	FadingRenderer* m_fadingText_wrongBallEnterHole;
	FadingRenderer* m_fadingText_ballEnterHoleScore;
	FadingRenderer* m_fadingText_ballEnterHoleScoreConsecutive;
	FadingRenderer* m_fadingText_ballEnterHoleScoreLast;
};