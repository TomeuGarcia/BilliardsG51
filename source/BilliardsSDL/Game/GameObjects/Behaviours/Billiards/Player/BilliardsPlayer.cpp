#include "BilliardsPlayer.h"

BilliardsPlayer::BilliardsPlayer()
	: m_stick(nullptr),
	m_score(10, 15, 30)
{
}

BilliardsPlayer::~BilliardsPlayer()
{
}

void BilliardsPlayer::Init(BilliardStick* stick, const Color& backgroundColor, const std::set<BilliardBall*>& remainingColoredBalls)
{
	m_stick = stick;
	m_backgroundColor = backgroundColor;
	m_remainingColoredBalls = remainingColoredBalls;
}

BilliardStick* BilliardsPlayer::GetStick() const
{
	return m_stick;
}

BilliardsScore& BilliardsPlayer::GetScore()
{
	return m_score;
}

Color BilliardsPlayer::GetBackgroundColor() const
{
	return m_backgroundColor;
}

bool BilliardsPlayer::StillHasRemainingColoredBalls() const
{
	return m_remainingColoredBalls.size() > 0;
}

void BilliardsPlayer::RemoveRemainingColoredBall(BilliardBall* ball)
{
	m_remainingColoredBalls.erase(ball);
}
