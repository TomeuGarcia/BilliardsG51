#pragma once
#include <algorithm>

#include "IBilliardsGameplayStateEventsManager.h"
#include "../Player/BilliardsPlayer.h"
#include "../BilliardBall.h"


class BilliardsGameplayStateBlackboard
{
public:
	BilliardsGameplayStateBlackboard();
	~BilliardsGameplayStateBlackboard();

	void Init(const std::vector<BilliardBall*>& balls, const Vector2<float>& boardCenter,
		BilliardsPlayer* playerRed, BilliardsPlayer* playerBlue,
		IBilliardsGameplayStateEventsManager* specialEventsManager);


	BilliardsPlayer* GetPlayerRed();
	BilliardsPlayer* GetPlayerBlue();
	void SetCurrentPlayer(BilliardsPlayer* currentPlayer);
	BilliardsPlayer* GetCurrentPlayer() const;
	BilliardsPlayer* GetOtherPlayer() const;

	const std::vector<BilliardBall*>& GetBalls() const;

	IBilliardsGameplayStateEventsManager* GetSpecialEventsManager();

	Vector2<float> GetBoardCenter() const;
	float GetStickForceOverDistanceMultiplier() const;
	float GetPinPullMaxDistance() const;



public:
	Vector2<float> p_pinPosition;
	Vector2<float> p_directionToPinPosition;
	float p_pinPullDistanceForHit;

	bool p_victoryAchieved;


private:
	BilliardsPlayer* m_playerRed;
	BilliardsPlayer* m_playerBlue;
	BilliardsPlayer* m_currentPlayer;

	std::vector<BilliardBall*> m_balls;

	IBilliardsGameplayStateEventsManager* m_specialEventsManager;

	Vector2<float> m_boardCenter;

	float m_stickForceOverDistanceMultiplier;

	float m_pinPullMaxDistance;
};