#include "BilliardsGameplayStateBlackboard.h"

BilliardsGameplayStateBlackboard::BilliardsGameplayStateBlackboard()
	: m_playerRed(nullptr), m_playerBlue(nullptr), m_currentPlayer(nullptr), m_boardCenter(), 
	m_balls(), m_whiteBall(nullptr),
	m_specialEventsManager(nullptr),
	m_pinPullMinDistance(0.1f),
	m_pinPullMaxDistance(1.5f),
	m_stickForceOverDistanceMultiplier(13.3f),
	p_victoryAchieved(false)
{}

BilliardsGameplayStateBlackboard::~BilliardsGameplayStateBlackboard()
{}

void BilliardsGameplayStateBlackboard::Init(const std::vector<BilliardBall*>& balls, BilliardBall* whiteBall,
	const Vector2<float>& boardCenter,
	BilliardsPlayer* playerRed, BilliardsPlayer* playerBlue,
	IBilliardsGameplayStateEventsManager* specialEventsManager)
{
	m_balls.resize(balls.size());
	std::copy(balls.begin(), balls.end(), std::begin(m_balls));
	m_whiteBall = whiteBall;
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

BilliardsPlayer* BilliardsGameplayStateBlackboard::GetOtherPlayer() const
{
	return m_currentPlayer == m_playerRed ? m_playerBlue : m_playerRed;
}


void BilliardsGameplayStateBlackboard::SetWinnerPlayer(BilliardsPlayer* winnerPlayer)
{
	m_winnerPlayer = winnerPlayer;
}

BilliardsPlayer* BilliardsGameplayStateBlackboard::GetWinnerPlayer() const
{
	return m_winnerPlayer;
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

float BilliardsGameplayStateBlackboard::GetPinPullMinDistance() const
{
	return m_pinPullMinDistance;
}

float BilliardsGameplayStateBlackboard::GetPinPullMaxDistance() const
{
	return m_pinPullMaxDistance;
}

bool BilliardsGameplayStateBlackboard::GetCanHitWhiteBall() const
{
	return m_canHitWhiteBall;
}

void BilliardsGameplayStateBlackboard::SetCanHitWhiteBall(const bool& canHitWhiteBall)
{
	m_canHitWhiteBall = canHitWhiteBall;
}

Vector2<float> BilliardsGameplayStateBlackboard::GetWhiteBallPosition() const
{
	return m_whiteBall->GetTransform()->p_worldPosition;
}
