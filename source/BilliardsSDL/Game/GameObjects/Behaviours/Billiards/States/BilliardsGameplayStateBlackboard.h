#pragma once
#include <algorithm>

#include "../Player/BilliardsPlayer.h"
#include "../BilliardBall.h"


class BilliardsGameplayStateBlackboard
{
public:
	BilliardsGameplayStateBlackboard();
	~BilliardsGameplayStateBlackboard();

	void Init(const std::vector<BilliardBall*>& balls, const Vector2<float>& boardCenter,
		BilliardsPlayer* playerRed, BilliardsPlayer* playerBlue);


	BilliardsPlayer* GetPlayerRed();
	BilliardsPlayer* GetPlayerBlue();
	void SetCurrentPlayer(BilliardsPlayer* currentPlayer);
	BilliardsPlayer* GetCurrentPlayer() const;

	const std::vector<BilliardBall*>& GetBalls() const;

	Vector2<float> GetBoardCenter() const;


private:
	BilliardsPlayer* m_playerRed;
	BilliardsPlayer* m_playerBlue;
	BilliardsPlayer* m_currentPlayer;

	std::vector<BilliardBall*> m_balls;

	Vector2<float> m_boardCenter;
};