#include "AABoxCollider2D.h"

AABoxCollider2D::AABoxCollider2D(GameObject* gameObject, Rigidbody2D* optionalRigidbody, const Vector2<float>& size)
	: Collider2D(gameObject, optionalRigidbody)
{
	SetWidth(size.x);
	SetHeight(size.y);
}

AABoxCollider2D::~AABoxCollider2D()
{
}

void AABoxCollider2D::SetWidth(const float& width)
{
	m_shape.width = width > 0 ? width : 0;
}

void AABoxCollider2D::SetHeight(const float& height)
{
	m_shape.height = height > 0 ? height : 0;
}

const Rect<float>& AABoxCollider2D::GetShape() const
{
	return m_shape;
}

void AABoxCollider2D::UpdateShape()
{
	const Vector2<float> center = GetGameObject()->GetTransform()->p_worldPosition;

	m_shape.x = center.x - (m_shape.width / 2.0f);
	m_shape.y = center.y + (m_shape.height / 2.0f);
}

