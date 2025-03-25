#include "Collider2D.h"

Collider2D::Collider2D(GameObject* gameOject)
	: m_gameObject(gameOject)
{
}

Collider2D::~Collider2D()
{
}

GameObject* Collider2D::GetGameObject()
{
	return m_gameObject;
}
