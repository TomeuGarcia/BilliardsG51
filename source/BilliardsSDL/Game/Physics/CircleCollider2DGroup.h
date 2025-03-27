#pragma once
#include <map>
#include <vector>
#include <memory>
#include "Collision/Collision2D.h"
#include "Colliders/CircleCollider2D.h"


class CircleCollider2DGroup
{
public:
	CircleCollider2DGroup();
	~CircleCollider2DGroup();

	void Clear();

	void AddCollider(const std::shared_ptr<CircleCollider2D>& collider, const bool& hasRigidbody);

	void UpdateActiveCollision(CircleCollider2D* colliderA, Collider2D* colliderB, const bool& areColliding, 
		bool& outWereAlreadyColliding);


private:
	void AddActiveCollision(CircleCollider2D* colliderWithRigidbody, Collider2D* otherCollider,
		std::vector<Collision2D>::iterator& outCollisionIt);
	bool GetActiveCollision(CircleCollider2D* colliderWithRigidbody, Collider2D* otherCollider,
		std::vector<Collision2D>::iterator& outCollisionIt);
	void RemoveActiveCollision(CircleCollider2D* colliderWithRigidbody,
		const std::vector<Collision2D>::iterator& collisionIt);


public:
	std::vector<std::shared_ptr<CircleCollider2D>> p_rigidbodyColliders;
	std::vector<std::shared_ptr<CircleCollider2D>> p_rigidbodylessColliders;
private:
	std::map<CircleCollider2D*, std::vector<Collision2D>> m_activeCollisionsByRigidbodyCollider;
};