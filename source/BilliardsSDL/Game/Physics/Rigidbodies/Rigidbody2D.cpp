#include "Rigidbody2D.h"

Rigidbody2D::Rigidbody2D(const std::shared_ptr<Collider2D>& collider, const std::shared_ptr<PhysicMaterial>& physicMaterial,
						 const float& mass, const float& gravityScale)
	: m_collider(collider), m_physicMaterial(physicMaterial), p_mass(mass), p_gravityScale(gravityScale),
	p_position(collider->GetGameObject()->GetTransform()->p_worldPosition),
	p_velocity(Vector2<float>::Zero()),
	m_acceleration(Vector2<float>::Zero()),
	m_deceleration(Vector2<float>::Zero())
{
}

Rigidbody2D::~Rigidbody2D()
{
}



Vector2<float> Rigidbody2D::GetAcceleration() const
{
	return m_acceleration + m_deceleration;
}

PhysicMaterial* Rigidbody2D::GetPhysicMaterial() const
{
	return m_physicMaterial.get();
}

Collider2D* Rigidbody2D::GetCollider() const
{
	return m_collider.get();
}



void Rigidbody2D::UpdatePosition()
{
	m_collider->GetGameObject()->GetTransform()->p_worldPosition = p_position;
}

void Rigidbody2D::ApplyFriction()
{
	const float speed = p_velocity.Length();
	if (speed < 0.01f)
	{
		m_deceleration = p_velocity = Vector2<float>::Zero();
		return;
	}

	m_deceleration = (p_velocity / speed) * -m_physicMaterial->GetFriction();
}



void Rigidbody2D::ApplyForce(const Vector2<float>& force)
{
	m_acceleration += ComputeForceAcceleration(force);
}

Vector2<float> Rigidbody2D::ComputeGravityForceAcceleration(const Vector2<float>& gravityForce)
{
	return ComputeForceAcceleration(gravityForce) * p_gravityScale;
}

Vector2<float> Rigidbody2D::ComputeForceAcceleration(const Vector2<float>& force)
{
	return force / p_mass;
}