#include "EulerSolver.h"

EulerSolver::EulerSolver(const Vector2<float>& gravityForce)
	: m_gravityForce(gravityForce)
{
}

EulerSolver::~EulerSolver()
{
}

void EulerSolver::Step(const float& deltaTime, Rigidbody2D& rigidbody)
{
	rigidbody.p_position = rigidbody.p_position + (rigidbody.GetVelocity() * deltaTime);

	const Vector2<float> combinedAcceleration = rigidbody.ComputeGravityForceAcceleration(m_gravityForce) + 
												rigidbody.GetAcceleration();

	rigidbody.SetVelocity(rigidbody.GetVelocity() + (combinedAcceleration * deltaTime));
}
