#include "Collider2D.h"

Collider2D::Collider2D(GameObject* gameOject, Rigidbody2D* optionalRigidbody, const bool& isTrigger)
	: m_gameObject(gameOject), m_rigidbody(optionalRigidbody), m_isTrigger(isTrigger)
{
}

Collider2D::~Collider2D()
{
}

GameObject* Collider2D::GetGameObject() const
{
	return m_gameObject;
}

bool Collider2D::HasRigidbody()
{
	return m_rigidbody != nullptr;
}

Rigidbody2D* Collider2D::GetRigidbody() const
{
	return m_rigidbody;
}

bool Collider2D::GetIsTrigger() const
{
	return m_isTrigger;
}
