#include "BallCollision.h"

BallCollision::BallCollision(GameObject* ballGameObject, GameObject* otherGameObject, 
	const float& ballSpeed, const bool& otherIsAlsoABall)
	: m_ballGameObject(ballGameObject), m_otherGameObject(otherGameObject),
	m_ballSpeed(ballSpeed), m_collisionBetweenBalls(otherIsAlsoABall)
{
}

bool BallCollision::TheSameGameObjectsCollided(const BallCollision& other)
{
	return (m_ballGameObject == other.m_ballGameObject && m_otherGameObject == other.m_otherGameObject) ||
	       (m_ballGameObject == other.m_otherGameObject && m_otherGameObject == other.m_ballGameObject);
}

float BallCollision::GetBallSpeed() const
{
	return m_ballSpeed;
}

bool BallCollision::IsBetweenBalls() const
{
	return m_collisionBetweenBalls;
}
