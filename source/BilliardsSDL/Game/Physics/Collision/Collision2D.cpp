#include "Collision2D.h"

Collision2D::Collision2D(Collider2D* colliderA, Collider2D* colliderB)
	: m_colliderA(colliderA), m_colliderB(colliderB), m_status(Status::None)
{
}

Collision2D::~Collision2D()
{
}

void Collision2D::UpdateStatus(const bool& keepColliding)
{
	if (keepColliding)
	{
		if (m_status == Status::None)
		{
			m_status = Status::Enter;		
		}
		else if (m_status == Status::Enter)
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
