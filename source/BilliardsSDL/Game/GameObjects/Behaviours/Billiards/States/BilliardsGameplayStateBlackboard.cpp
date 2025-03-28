#include "BilliardsGameplayStateBlackboard.h"

BilliardsGameplayStateBlackboard::BilliardsGameplayStateBlackboard()
	: m_playerRed(nullptr), m_playerBlue(nullptr), m_currentPlayer(nullptr), m_boardCenter(), m_balls(),
	m_specialEventsManager(nullptr),
	m_pinPullMaxDistance(2.0f),
	m_stickForceOverDistanceMultiplier(10.0f),
	p_victoryAchieved(false)
{}

BilliardsGameplayStateBlackboard::~BilliardsGameplayStateBlackboard()
{}

void BilliardsGameplayStateBlackboard::Init(const std::vector<BilliardBall*>& balls, const Vector2<float>& boardCenter,
	BilliardsPlayer* playerRed, BilliardsPlayer* playerBlue,
	IBilliardsGameplayStateEventsManager* specialEventsManager)
{
	m_balls.resize(balls.size());
	std::copy(balls.begin(), balls.end(), std::begin(m_balls));
	m_boardCenter = boardCenter;
	m_playerRed = playerRed;
	m_playerBlue = playerBlue;
	m_specialEventsManager = specialEventsManager;
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

IBilliardsGameplayStateEventsManager* BilliardsGameplayStateBlackboard::GetSpecialEventsManager()
{
	return m_specialEventsManager;
}

Vector2<float> BilliardsGameplayStateBlackboard::GetBoardCenter() const
{
	return m_boardCenter;
}

float BilliardsGameplayStateBlackboard::GetStickForceOverDistanceMultiplier() const
{
	return m_stickForceOverDistanceMultiplier;
}

float BilliardsGameplayStateBlackboard::GetPinPullMaxDistance() const
{
	return m_pinPullMaxDistance;
}
