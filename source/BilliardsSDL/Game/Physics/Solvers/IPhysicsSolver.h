#pragma once
#include "../Rigidbodies/Rigidbody2D.h"


class IPhysicsSolver
{
public:
	virtual void Step(const float& deltaTime, Rigidbody2D& rigidbody) = 0;
};