#pragma once
#include "../BilliardBall.h"



class IBilliardBoardHoleInteractionsManager
{
public:
	virtual void OnBallEnteredHole(BilliardBall* ball, const Vector2<float>& holeCenter) = 0;

};