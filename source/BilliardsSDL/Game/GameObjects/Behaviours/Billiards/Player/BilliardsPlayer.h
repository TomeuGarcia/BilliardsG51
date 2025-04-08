#pragma once
#include <set>
#include "../BilliardStick.h"
#include "BilliardsScore.h"
#include "../BilliardBall.h"


class BilliardsPlayer
{
public:
	BilliardsPlayer(const BilliardsScore::Configuration& scoreConfiguration);
	~BilliardsPlayer();

	void Init(BilliardStick* stick, const Color& backgroundColor, const std::set<BilliardBall*>& remainingColoredBalls,
		const std::string& name);

	const std::string& GetName() const;
	BilliardStick* GetStick() const;
	BilliardsScore& GetScore();
	Color GetBackgroundColor() const;

	bool StillHasRemainingColoredBalls() const;
	void RemoveRemainingColoredBall(BilliardBall* ball);


private:
	std::string m_name;

	BilliardStick* m_stick;
	BilliardsScore m_score;
	Color m_backgroundColor;

	std::set<BilliardBall*> m_remainingColoredBalls;
};