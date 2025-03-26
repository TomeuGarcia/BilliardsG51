#include "AABoxCollider2D.h"

AABoxCollider2D::AABoxCollider2D(GameObject* gameObject, Rigidbody2D* optionalRigidbody, const bool& isTrigger, 
	const Vector2<float>& size)
	: Collider2D(gameObject, optionalRigidbody, isTrigger)
{
	SetSize(size);
	UpdateShape();
}

AABoxCollider2D::~AABoxCollider2D()
{
}

void AABoxCollider2D::SetSize(const Vector2<float>& size)
{
	Vector2<float> fixedSize(
		size.x > 0 ? size.x : 0,
		size.y > 0 ? size.y : 0
	);

	m_shape.SetSize(fixedSize);
}

const Rect<float>& AABoxCollider2D::GetShape() const
{
	return m_shape;
}

void AABoxCollider2D::UpdateShape()
{
	const Vector2<float> center = GetGameObject()->GetTransform()->p_worldPosition;
	m_shape.SetCenterPosition(center);
}

