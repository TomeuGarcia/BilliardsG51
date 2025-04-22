#pragma once
#include "../../Behaviour.h"
#include "../BilliardBall.h"
#include "IBallCollisionFeedbackManager.h"


class BallCollisionDetector : public Behaviour
{
public:
	BallCollisionDetector(GameObject* ownerGameObject, BilliardBall* ball, IBallCollisionFeedbackManager* collisionFeedbackManager);


	virtual void OnCollisionEnter(GameObject* other) override;


private:
	GameObject* m_ownerGameObject;
	BilliardBall* m_ball;
	IBallCollisionFeedbackManager* m_collisionFeedbackManager;
};