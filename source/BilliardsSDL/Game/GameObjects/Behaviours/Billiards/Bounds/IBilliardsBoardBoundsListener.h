#pragma once
#include "../BilliardBall.h"


class IBilliardsBoardBoundsListener
{
public:
	virtual void OnBallExitsBoardBounds(BilliardBall* ball) = 0;
};