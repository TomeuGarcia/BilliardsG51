#include "AABoxCollider2DGroup.h"




AABoxCollider2DGroup::AABoxCollider2DGroup()
	: p_rigidbodyColliders(), p_rigidbodylessColliders(), m_activeCollisionsByRigidbodyCollider()
{
	p_rigidbodyColliders.reserve(15);
	p_rigidbodylessColliders.reserve(15);
}

AABoxCollider2DGroup::~AABoxCollider2DGroup()
{
	Clear();
}

void AABoxCollider2DGroup::Clear()
{
	p_rigidbodyColliders.clear();
	p_rigidbodylessColliders.clear();
	m_activeCollisionsByRigidbodyCollider.clear();
}



void AABoxCollider2DGroup::AddCollider(const std::shared_ptr<AABoxCollider2D>& collider, const bool& hasRigidbody)
{
	if (hasRigidbody)
	{
		p_rigidbodyColliders.emplace_back(collider);
		m_activeCollisionsByRigidbodyCollider[collider.get()] = {};
	}
	else
	{
		p_rigidbodylessColliders.emplace_back(collider);
	}
}



void AABoxCollider2DGroup::UpdateActiveCollision(AABoxCollider2D* colliderA, Collider2D* colliderB,
	const bool& areColliding)
{
	std::vector<Collision2D>::iterator outActiveCollision;
	if (GetActiveCollision(colliderA, outActiveCollision))
	{
		outActiveCollision->UpdateStatus(areColliding);
		if (outActiveCollision->GetStatus() == Collision2D::Status::Exit)
		{
			RemoveActiveCollision(colliderA, outActiveCollision);
		}
	}
	else if (areColliding)
	{
		AddActiveCollision(colliderA, colliderB, outActiveCollision);
	}
}




void AABoxCollider2DGroup::AddActiveCollision(AABoxCollider2D* colliderWithRigidbody, Collider2D* otherCollider,
	std::vector<Collision2D>::iterator& outCollisionIt)
{
	std::vector<Collision2D>& collisions = m_activeCollisionsByRigidbodyCollider[colliderWithRigidbody];
	collisions.emplace_back(colliderWithRigidbody, otherCollider);
	outCollisionIt = collisions.end() - 1;
}


bool AABoxCollider2DGroup::GetActiveCollision(AABoxCollider2D* colliderWithRigidbody,
	std::vector<Collision2D>::iterator& outCollisionIt)
{
	std::vector<Collision2D>& collisions = m_activeCollisionsByRigidbodyCollider[colliderWithRigidbody];

	for (auto it = collisions.begin(); it != collisions.end(); ++it)
	{
		if (it->GetColliderA() == colliderWithRigidbody)
		{
			outCollisionIt = it;
			return true;
		}
	}

	return false;
}


void AABoxCollider2DGroup::RemoveActiveCollision(AABoxCollider2D* colliderWithRigidbody,
	const std::vector<Collision2D>::iterator& collisionIt)
{
	std::vector<Collision2D>& collisions = m_activeCollisionsByRigidbodyCollider[colliderWithRigidbody];
	collisions.erase(collisionIt);
}