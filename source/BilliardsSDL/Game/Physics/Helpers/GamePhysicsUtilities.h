#pragma once
#include "../Physics2DManager.h"
#include "../../Systems/GameRandom.h"


namespace GamePhysicsUtilities
{
	Vector2<float> FindRandomPositionWithoutObstacles(const Vector2<float> center, const Vector2<float> signedBounds,
		const float& obstacleCheckRadius, const int& maxTries);
}