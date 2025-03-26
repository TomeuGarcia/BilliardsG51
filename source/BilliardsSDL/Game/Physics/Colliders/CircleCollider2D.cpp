#include "CircleCollider2D.h"

CircleCollider2D::CircleCollider2D(GameObject* gameObject, Rigidbody2D* optionalRigidbody, const float& radius)
	: Collider2D(gameObject, optionalRigidbody), 
	m_shape(gameObject->GetTransform()->p_worldPosition, radius)
{
	UpdateShape();
}

CircleCollider2D::~CircleCollider2D()
{
}

void CircleCollider2D::SetRadius(const float& radius)
{
	m_shape.SetRadius(radius);
}

const Circle& CircleCollider2D::GetShape() const
{
	return m_shape;
}

void CircleCollider2D::UpdateShape()
{
	m_shape.p_position = GetGameObject()->GetTransform()->p_worldPosition;
}
