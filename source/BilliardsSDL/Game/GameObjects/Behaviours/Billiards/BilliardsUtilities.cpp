#include "BilliardsUtilities.h"


namespace BilliardsUtilities
{

	void PositionBallsRandomly(const std::vector<BilliardBall*>& balls, const Vector2<float>& boardCenter, const Vector2<float>& boardBounds)
	{
		const float checkRadius = 0.5f;

		for (auto it = balls.begin(); it != balls.end(); ++it)
		{
			Vector2<float> position = GamePhysicsUtilities::FindRandomPositionWithoutObstacles(boardCenter, boardBounds, checkRadius, 5);
			(*it)->SetPosition(position);
		}
	}

}


