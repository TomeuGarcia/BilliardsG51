#pragma once

class BilliardBall;
class BilliardsBoardHole;

class IBilliardBoardHoleInteractionsManager
{
public:
	virtual void OnBallEnteredHole(BilliardsBoardHole* hole, BilliardBall* ball) = 0;

};