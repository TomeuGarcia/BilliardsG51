#pragma once
#include <set>
#include "../BilliardStick.h"
#include "BilliardsScore.h"
#include "../BilliardBall.h"


class BilliardsPlayer
{
public:
	BilliardsPlayer();
	~BilliardsPlayer();

	void Init(BilliardStick* stick, const Color& backgroundColor, const std::set<BilliardBall*>& remainingColoredBalls);

	BilliardStick* GetStick() const;
	BilliardsScore& GetScore();
	Color GetBackgroundColor() const;

	bool StillHasRemainingColoredBalls() const;
	void RemoveRemainingColoredBall(BilliardBall* ball);


private:
	BilliardStick* m_stick;
	BilliardsScore m_score;
	Color m_backgroundColor;

	std::set<BilliardBall*> m_remainingColoredBalls;
};