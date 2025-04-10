#pragma once
#include "../../../GameObject.h"


class BallCollision
{
public:
	BallCollision(GameObject* ballGameObject, GameObject* otherGameObject, 
		const float& ballSpeed, const bool& otherIsAlsoABall);

	bool TheSameGameObjectsCollided(const BallCollision& other);

	float GetBallSpeed() const;
	bool IsBetweenBalls() const;

private:
	GameObject* m_ballGameObject;
	GameObject* m_otherGameObject;
	
	float m_ballSpeed;
	bool m_collisionBetweenBalls;

};