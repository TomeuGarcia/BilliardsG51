#include "BallCollisionDetector.h"



BallCollisionDetector::BallCollisionDetector(GameObject* ownerGameObject, BilliardBall* ball, 
	IBallCollisionFeedbackManager* collisionFeedbackManager)
	: m_ownerGameObject(ownerGameObject), m_ball(ball), m_collisionFeedbackManager(collisionFeedbackManager)
{
}

void BallCollisionDetector::OnCollisionEnter(GameObject* other)
{
	m_collisionFeedbackManager->AddCollisionToHandle(BallCollision{
		m_ownerGameObject,
		other,
		m_ball->GetCurrentSpeed(),
		other->HasTag(GameObjectTag::Ball)
		});
}
