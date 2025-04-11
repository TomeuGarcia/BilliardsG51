#pragma once
#include "../Behaviour.h"
#include "../../GameObjectGroup.h"
#include "../Billiards/Holes/IBilliardBoardHoleInteractionsManager.h"




class MainMenuManager : 
	public Behaviour,
	public IBilliardBoardHoleInteractionsManager
{
public:
	MainMenuManager();

	void OnBallEnteredHole(BilliardBall* ball, const Vector2<float>& holeCenter) override;
};