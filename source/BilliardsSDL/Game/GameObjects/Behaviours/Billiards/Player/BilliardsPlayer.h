#pragma once
#include "../BilliardStick.h"
#include "BilliardsScore.h"


class BilliardsPlayer
{
public:
	BilliardsPlayer();
	~BilliardsPlayer();

	void Init(BilliardStick* stick);

	BilliardStick* GetStick() const;
	BilliardsScore& GetScore();


private:
	BilliardStick* m_stick;
	BilliardsScore m_score;

};