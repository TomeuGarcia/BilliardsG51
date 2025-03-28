#pragma once
#include "../BilliardBall.h"
#include "IBilliardBoardHoleInteractionsManager.h"


class BilliardsBoardHole : public Behaviour
{
public:
	BilliardsBoardHole(Transform* transform, IBilliardBoardHoleInteractionsManager* interactionManager);
	virtual ~BilliardsBoardHole();


	virtual void OnTriggerEnter(GameObject* other) override;



private:
	Transform* m_transform;
	IBilliardBoardHoleInteractionsManager* m_interactionManager;

};