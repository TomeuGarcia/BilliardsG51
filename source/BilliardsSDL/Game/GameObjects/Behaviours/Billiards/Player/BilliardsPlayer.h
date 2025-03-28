#pragma once
#include "../BilliardStick.h"
#include "BilliardsScore.h"


class BilliardsPlayer
{
public:
	BilliardsPlayer();
	~BilliardsPlayer();

	void Init(BilliardStick* stick, const Color& backgroundColor);

	BilliardStick* GetStick() const;
	BilliardsScore& GetScore();
	Color GetBackgroundColor() const;


private:
	BilliardStick* m_stick;
	BilliardsScore m_score;
	Color m_backgroundColor;

};