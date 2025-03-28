#include "BilliardsPlayer.h"

BilliardsPlayer::BilliardsPlayer()
	: m_stick(nullptr),
	m_score(10, 15, 30)
{
}

BilliardsPlayer::~BilliardsPlayer()
{
}

void BilliardsPlayer::Init(BilliardStick* stick)
{
	m_stick = stick;
}

BilliardStick* BilliardsPlayer::GetStick() const
{
	return m_stick;
}

BilliardsScore& BilliardsPlayer::GetScore()
{
	return m_score;
}
