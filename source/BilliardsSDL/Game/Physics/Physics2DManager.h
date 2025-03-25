#pragma once
#include "../../Shared/Math/Math.h"
#include "EulerSolver.h"
#include "Collision/Collision2D.h"


class Physics2DManager
{
public:
	Physics2DManager();
	~Physics2DManager();

public:
	static Physics2DManager* GetInstance();


public:
	void ClearReferences();
	void AddRigidbody(const std::shared_ptr<Rigidbody2D>& rigidbody);
	void AddRigidbodylessCollider(const std::shared_ptr<Collider2D>& collider);
	void RemoveRigidbodylessCollider(const std::shared_ptr<Collider2D>& collider);

	void Update(const float& deltaTime);

private:
	void UpdateRigidbodies(const float& deltaTime);
	void UpdateRigidbodylessColliders();
	void UpdateCollisions();


private:
	EulerSolver m_solver;

	std::vector<std::shared_ptr<Rigidbody2D>> m_rigidbodies;
	std::vector<std::shared_ptr<Collider2D>> m_rigidbodylessColliders;
	std::vector<Collision2D> m_activeCollisions;

private:
	static Physics2DManager* s_instance;
};