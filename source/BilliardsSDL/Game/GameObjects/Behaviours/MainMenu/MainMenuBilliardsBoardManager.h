#pragma once
#include "../Billiards/Holes/IBilliardBoardHoleInteractionsManager.h"
#include "../Billiards/BallFeedback/IBallCollisionFeedbackManager.h"


class MainMenuBilliardsBoardManager : 
	public IBilliardBoardHoleInteractionsManager,
	public IBallCollisionFeedbackManager
{
public:
	MainMenuBilliardsBoardManager();

public:
	virtual void OnBallEnteredHole(BilliardBall* ball, const Vector2<float>& holeCenter) override;
	virtual void AddCollisionToHandle(const BallCollision& ballCollision) override;
};