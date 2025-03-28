#include "BilliardsGameplayStateBlackboard.h"

BilliardsGameplayStateBlackboard::BilliardsGameplayStateBlackboard()
	: m_playerRed(nullptr), m_playerBlue(nullptr), m_currentPlayer(nullptr), m_boardCenter(), m_balls()
{}

BilliardsGameplayStateBlackboard::~BilliardsGameplayStateBlackboard()
{}

void BilliardsGameplayStateBlackboard::Init(const std::vector<BilliardBall*>& balls, const Vector2<float>& boardCenter,
	BilliardsPlayer* playerRed, BilliardsPlayer* playerBlue)
{
	m_balls.resize(balls.size());
	std::copy(balls.begin(), balls.end(), std::begin(m_balls));
	m_boardCenter = boardCenter;
	m_playerRed = playerRed;
	m_playerBlue = playerBlue;
}


BilliardsPlayer* BilliardsGameplayStateBlackboard::GetPlayerRed()
{
	return m_playerRed;
}

BilliardsPlayer* BilliardsGameplayStateBlackboard::GetPlayerBlue()
{
	return m_playerBlue;
}

void BilliardsGameplayStateBlackboard::SetCurrentPlayer(BilliardsPlayer* currentPlayer)
{
	m_currentPlayer = currentPlayer;
}

BilliardsPlayer* BilliardsGameplayStateBlackboard::GetCurrentPlayer() const
{
	return m_currentPlayer;
}


const std::vector<BilliardBall*>& BilliardsGameplayStateBlackboard::GetBalls() const
{
	return m_balls;
}

Vector2<float> BilliardsGameplayStateBlackboard::GetBoardCenter() const
{
	return m_boardCenter;
}
