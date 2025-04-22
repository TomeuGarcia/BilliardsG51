#pragma once
#include <vector>
#include "BilliardBall.h"

#include "../../../Physics/Helpers/GamePhysicsUtilities.h"


namespace BilliardsUtilities
{
	void PositionBallsRandomly(const std::vector<BilliardBall*>& balls, const Vector2<float>& boardCenter, const Vector2<float>& boardBounds);
}