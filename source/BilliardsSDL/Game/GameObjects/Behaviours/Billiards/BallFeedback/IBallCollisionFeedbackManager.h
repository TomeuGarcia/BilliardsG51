#pragma once
#include "BallCollision.h"


class IBallCollisionFeedbackManager
{
public:
	virtual void AddCollisionToHandle(const BallCollision& ballCollision) = 0;
};