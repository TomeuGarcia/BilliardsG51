#include "BilliardsPlayer.h"

BilliardsPlayer::BilliardsPlayer()
	: m_stick(nullptr),
	m_score(10, 15, 30)
{
}

BilliardsPlayer::~BilliardsPlayer()
{
}

void BilliardsPlayer::Init(BilliardStick* stick, const Color& backgroundColor)
{
	m_stick = stick;
	m_backgroundColor = backgroundColor;
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
