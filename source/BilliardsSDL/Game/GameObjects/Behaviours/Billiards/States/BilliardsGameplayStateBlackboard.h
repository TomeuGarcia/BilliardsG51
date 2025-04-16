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

	void Init(const std::vector<BilliardBall*>& balls, BilliardBall* whiteBall,
		const Vector2<float>& boardCenter,
		BilliardsPlayer* playerRed, BilliardsPlayer* playerBlue,
		IBilliardsGameplayStateEventsManager* specialEventsManager);


	BilliardsPlayer* GetPlayerRed();
	BilliardsPlayer* GetPlayerBlue();
	void SetCurrentPlayer(BilliardsPlayer* currentPlayer);
	BilliardsPlayer* GetCurrentPlayer() const;
	BilliardsPlayer* GetOtherPlayer() const;

	void SetWinnerPlayer(BilliardsPlayer* winnerPlayer);
	BilliardsPlayer* GetWinnerPlayer() const;


	const std::vector<BilliardBall*>& GetBalls() const;

	IBilliardsGameplayStateEventsManager* GetSpecialEventsManager();

	Vector2<float> GetBoardCenter() const;
	float GetStickForceOverDistanceMultiplier() const;
	float GetPinPullMinDistance() const;
	float GetPinPullMaxDistance() const;

	bool GetCanHitWhiteBall() const;
	void SetCanHitWhiteBall(const bool& canHitWhiteBall);

	Vector2<float> GetWhiteBallPosition() const;
	float GetWhiteBallRadius() const;

	bool GetSamePlayerIsPlayingConsecutiveTurns() const;
	void SetSamePlayerIsPlayingConsecutiveTurns(const bool& samePlayerIsPlayingConsecutiveTurns);

	bool GetPreviewHitDirectionIsVisible() const;
	void SetPreviewHitDirectionIsVisible(const bool& previewHitDirectionIsVisible);


public:
	Vector2<float> p_pinPosition;
	Vector2<float> p_directionToPinPosition;
	float p_pinPullDistanceForHit;

	bool p_victoryAchieved;


private:
	BilliardsPlayer* m_playerRed;
	BilliardsPlayer* m_playerBlue;
	BilliardsPlayer* m_currentPlayer;
	BilliardsPlayer* m_winnerPlayer;

	std::vector<BilliardBall*> m_balls;
	BilliardBall* m_whiteBall;

	IBilliardsGameplayStateEventsManager* m_specialEventsManager;

	Vector2<float> m_boardCenter;

	float m_stickForceOverDistanceMultiplier;

	float m_pinPullMinDistance;
	float m_pinPullMaxDistance;

	bool m_canHitWhiteBall;

	bool m_samePlayerIsPlayingConsecutiveTurns;

	bool m_previewHitDirectionIsVisible;
};