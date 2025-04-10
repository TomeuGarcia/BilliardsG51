#include "Collision2D.h"

Collision2D::Collision2D(Collider2D* colliderA, Collider2D* colliderB)
	: m_colliderA(colliderA), m_colliderB(colliderB), m_status(Status::Enter)
{
	NotifyEnter();
}

Collision2D::~Collision2D()
{
}

void Collision2D::UpdateStatus(const bool& keepColliding)
{
	if (keepColliding)
	{
		if (m_status == Status::Enter)
		{
			m_status = Status::Stay;
		}
	}
	else
	{
		m_status = Status::Exit;
	}
}

Collider2D* Collision2D::GetColliderA() const
{
	return m_colliderA;
}

Collider2D* Collision2D::GetColliderB() const
{
	return m_colliderB;
}

const Collision2D::Status Collision2D::GetStatus() const
{
	return m_status;
}



void Collision2D::NotifyEnter()
{
	const bool bothAreColliders = !m_colliderA->GetIsTrigger() && !m_colliderB->GetIsTrigger();
	const std::vector<std::shared_ptr<Behaviour>>& behavioursA = m_colliderA->GetGameObject()->GetBehaviours();
	const std::vector<std::shared_ptr<Behaviour>>& behavioursB = m_colliderB->GetGameObject()->GetBehaviours();
	GameObject* otherForA = m_colliderB->GetGameObject();
	GameObject* otherForB = m_colliderA->GetGameObject();

	if (bothAreColliders)
	{
		for (auto it = behavioursA.begin(); it != behavioursA.end(); ++it)
		{
			(*it)->OnCollisionEnter(otherForA);
		}
		for (auto it = behavioursB.begin(); it != behavioursB.end(); ++it)
		{
			(*it)->OnCollisionEnter(otherForB);
		}
	}
	else
	{
		for (auto it = behavioursA.begin(); it != behavioursA.end(); ++it)
		{
			(*it)->OnTriggerEnter(otherForA);
		}
		for (auto it = behavioursB.begin(); it != behavioursB.end(); ++it)
		{
			(*it)->OnTriggerEnter(otherForB);
		}
	}
}
