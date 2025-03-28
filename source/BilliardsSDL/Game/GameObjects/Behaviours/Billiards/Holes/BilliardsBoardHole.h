#pragma once
#include "../BilliardBall.h"
#include "IBilliardBoardHoleInteractionsManager.h"


class BilliardsBoardHole : Behaviour
{
public:
	BilliardsBoardHole(Transform* transform, IBilliardBoardHoleInteractionsManager* interactionManager);
	virtual ~BilliardsBoardHole();

	Vector2<float> GetCenterPosition() const;


	virtual void OnTriggerEnter(GameObject* other) override;



private:
	Transform* m_transform;
	IBilliardBoardHoleInteractionsManager* m_interactionManager;

};