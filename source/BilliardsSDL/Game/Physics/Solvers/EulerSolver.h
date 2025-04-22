#pragma once
#include "IPhysicsSolver.h"


class EulerSolver : public IPhysicsSolver
{
public:
	EulerSolver(const Vector2<float>& gravityForce);

	void Step(const float& deltaTime, Rigidbody2D& rigidbody);


private:
	Vector2<float> m_gravityForce;
};