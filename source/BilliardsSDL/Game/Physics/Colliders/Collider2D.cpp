#include "Collider2D.h"

Collider2D::Collider2D(GameObject* gameOject, Rigidbody2D* optionalRigidbody)
	: m_gameObject(gameOject), m_rigidbody(optionalRigidbody)
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
