#include "BilliardsPlayer.h"

BilliardsPlayer::BilliardsPlayer(const BilliardsScore::Configuration& scoreConfiguration)
	: m_stick(nullptr),
	m_score(scoreConfiguration),
	m_name(),
	m_backgroundColor(Colors::White)
{
}

BilliardsPlayer::~BilliardsPlayer()
{
}

void BilliardsPlayer::Init(BilliardStick* stick, const Color& backgroundColor, const std::set<BilliardBall*>& remainingColoredBalls,
	const std::string& name)
{
	m_name = name;
	m_stick = stick;
	m_backgroundColor = backgroundColor;
	m_remainingColoredBalls = remainingColoredBalls;
}

const std::string& BilliardsPlayer::GetName() const
{
	return m_name;
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
