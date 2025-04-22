#include "GamePhysicsUtilities.h"



namespace GamePhysicsUtilities
{
	Vector2<float> FindRandomPositionWithoutObstacles(const Vector2<float> center, const Vector2<float> signedBounds,
		const float& obstacleCheckRadius, const int& maxTries)
	{
		Vector2<float> randomPosition{};
		bool validPosition = false;
		int tries{ 0 };

		do
		{
			randomPosition = center + GameRandom::GetInstance()->GetRandomVectorBetweenSignedBounds(signedBounds);
			std::list<Collider2D*> overlaps = Physics2DManager::GetInstance()->CircleOverlap(randomPosition, obstacleCheckRadius);
			validPosition = overlaps.size() < 1;

			++tries;

		} while (!validPosition && tries < maxTries);

		return randomPosition;
	}
}