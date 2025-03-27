#pragma once
#include <map>
#include <vector>
#include <memory>
#include "Collision/Collision2D.h"
#include "Colliders/AABoxCollider2D.h"


class AABoxCollider2DGroup
{
public:
	AABoxCollider2DGroup();
	~AABoxCollider2DGroup();

	void Clear();

	void AddCollider(const std::shared_ptr<AABoxCollider2D>& collider, const bool& hasRigidbody);

	void UpdateActiveCollision(AABoxCollider2D* colliderA, Collider2D* colliderB, const bool& areColliding,
		bool& outWereAlreadyColliding);


private:
	void AddActiveCollision(AABoxCollider2D* colliderWithRigidbody, Collider2D* otherCollider,
		std::vector<Collision2D>::iterator& outCollisionIt);
	bool GetActiveCollision(AABoxCollider2D* colliderWithRigidbody, Collider2D* otherCollider,
		std::vector<Collision2D>::iterator& outCollisionIt);
	void RemoveActiveCollision(AABoxCollider2D* colliderWithRigidbody,
		const std::vector<Collision2D>::iterator& collisionIt);


public:
	std::vector<std::shared_ptr<AABoxCollider2D>> p_rigidbodyColliders;
	std::vector<std::shared_ptr<AABoxCollider2D>> p_rigidbodylessColliders;
private:
	std::map<AABoxCollider2D*, std::vector<Collision2D>> m_activeCollisionsByRigidbodyCollider;
};