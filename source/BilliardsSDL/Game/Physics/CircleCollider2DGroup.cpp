#include "CircleCollider2DGroup.h"




CircleCollider2DGroup::CircleCollider2DGroup()
	: p_rigidbodyColliders(), p_rigidbodylessColliders(), m_activeCollisionsByRigidbodyCollider()
{
	p_rigidbodyColliders.reserve(15);
	p_rigidbodylessColliders.reserve(15);
}

CircleCollider2DGroup::~CircleCollider2DGroup()
{
	Clear();
}

void CircleCollider2DGroup::Clear()
{
	p_rigidbodyColliders.clear();
	p_rigidbodylessColliders.clear();
	m_activeCollisionsByRigidbodyCollider.clear();
}



void CircleCollider2DGroup::AddCollider(const std::shared_ptr<CircleCollider2D>& collider, const bool& hasRigidbody)
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



void CircleCollider2DGroup::UpdateActiveCollision(CircleCollider2D* colliderA, Collider2D* colliderB,
	const bool& areColliding, bool& outWereAlreadyColliding)
{
	std::vector<Collision2D>::iterator outActiveCollision;
	outWereAlreadyColliding = GetActiveCollision(colliderA, colliderB, outActiveCollision);
	if (outWereAlreadyColliding)
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




void CircleCollider2DGroup::AddActiveCollision(CircleCollider2D* colliderWithRigidbody, Collider2D* otherCollider,
	std::vector<Collision2D>::iterator& outCollisionIt)
{
	std::vector<Collision2D>& collisions = m_activeCollisionsByRigidbodyCollider[colliderWithRigidbody];
	collisions.emplace_back(colliderWithRigidbody, otherCollider);
	outCollisionIt = collisions.end() - 1;
}


bool CircleCollider2DGroup::GetActiveCollision(CircleCollider2D* colliderWithRigidbody, Collider2D* otherCollider,
	std::vector<Collision2D>::iterator& outCollisionIt)
{
	std::vector<Collision2D>& collisions = m_activeCollisionsByRigidbodyCollider[colliderWithRigidbody];

	for (auto it = collisions.begin(); it != collisions.end(); ++it)
	{
		if (it->GetColliderA() == colliderWithRigidbody &&
			it->GetColliderB() == otherCollider)
		{
			outCollisionIt = it;
			return true;
		}
	}

	return false;
}


void CircleCollider2DGroup::RemoveActiveCollision(CircleCollider2D* colliderWithRigidbody,
	const std::vector<Collision2D>::iterator& collisionIt)
{
	std::vector<Collision2D>& collisions = m_activeCollisionsByRigidbodyCollider[colliderWithRigidbody];
	collisions.erase(collisionIt);
}