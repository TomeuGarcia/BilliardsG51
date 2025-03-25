#pragma once
#include "Rigidbodies/Rigidbody2D.h"

class EulerSolver
{
public:
	EulerSolver(const Vector2<float>& gravityForce);
	~EulerSolver();

	void Step(const float& deltaTime, Rigidbody2D& rigidbody);


private:
	Vector2<float> m_gravityForce;
};