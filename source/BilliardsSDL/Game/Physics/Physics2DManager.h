#pragma once
#include <map>
#include "../../Shared/Math/Math.h"
#include "Solvers/EulerSolver.h"
#include "Collision/Collision2D.h"
#include "Colliders/CircleCollider2D.h"
#include "Colliders/AABoxCollider2D.h"
#include "CircleCollider2DGroup.h"
#include "AABoxCollider2DGroup.h"
#include "Helpers/CollisionHelper.h"


class Physics2DManager
{
public:
	Physics2DManager();
	~Physics2DManager();

public:
	static Physics2DManager* GetInstance();


public:
	void ClearReferences();

	void AddCircleCollider(const std::shared_ptr<CircleCollider2D>& collider);
	void AddAABoxCollider(const std::shared_ptr<AABoxCollider2D>& collider);


	void Update(const float& deltaTime);


private:
	void UpdateRigidbodies(const float& deltaTime);
	void UpdateRigidbodylessColliders();
	void UpdateCollisions();

	void CheckCircleWithCircle(CircleCollider2D* circleColliderA, CircleCollider2D* circleColliderB);
	void CheckCircleWithAABox(CircleCollider2D* circleColliderA, AABoxCollider2D* aaBoxColliderB);
	void CheckAABoxWithCircle(AABoxCollider2D* aaBoxColliderA, CircleCollider2D* circleColliderB);
	void CheckAABoxWithAABox(AABoxCollider2D* aaBoxColliderA, AABoxCollider2D* aaBoxColliderB);


private:
	EulerSolver m_solver;
	CircleCollider2DGroup m_circleCollidersGroup;
	AABoxCollider2DGroup m_aaBoxCollidersGroup;

private:
	static Physics2DManager* s_instance;
};