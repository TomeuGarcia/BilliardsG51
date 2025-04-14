#pragma once
#include "../Billiards/Holes/IBilliardBoardHoleInteractionsManager.h"


class MainMenuBilliardsBoardManager : public IBilliardBoardHoleInteractionsManager
{
public:
	MainMenuBilliardsBoardManager();

public:
	virtual void OnBallEnteredHole(BilliardBall* ball, const Vector2<float>& holeCenter) override;
};