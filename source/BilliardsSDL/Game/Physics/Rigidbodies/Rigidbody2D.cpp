#include "Rigidbody2D.h"

Rigidbody2D::Rigidbody2D(GameObject* gameObject, 
						const std::shared_ptr<PhysicMaterial>& physicMaterial,
						const float& mass, const float& gravityScale)
	: m_gameObject(gameObject), m_physicMaterial(physicMaterial), p_mass(mass), p_gravityScale(gravityScale),
	m_position(gameObject->GetTransform()->p_worldPosition),
	m_velocity(Vector2<float>::Zero()), m_speed(0),
	m_acceleration(Vector2<float>::Zero()),
	m_isEnabled(true)
{
}

Rigidbody2D::~Rigidbody2D()
{
}


void Rigidbody2D::SetIsEnabled(const bool& isEnabled)
{
	m_isEnabled = isEnabled;
	if (isEnabled)
	{
		RefreshPosition();
	}
}

bool Rigidbody2D::GetIsEnabled() const
{
	return m_isEnabled;
}


const Vector2<float>& Rigidbody2D::GetPosition() const
{
	return m_position;
}

void Rigidbody2D::SetPosition(const Vector2<float>& position)
{
	m_position = position;
}


const Vector2<float>& Rigidbody2D::GetVelocity() const
{
	return m_velocity;
}

void Rigidbody2D::SetVelocity(const Vector2<float>& velocity)
{
	m_velocity = velocity;
	m_speed = m_velocity.Length();
	m_moveDirection = m_velocity / m_speed;
}




const Vector2<float>& Rigidbody2D::GetAcceleration() const
{
	return m_acceleration;
}

void Rigidbody2D::SetAcceleration(const Vector2<float>& acceleration)
{
	m_acceleration = acceleration;
}

const float Rigidbody2D::GetSpeed() const
{
	return m_speed;
}

const Vector2<float> Rigidbody2D::GetMomentum() const
{
	if (IsAtRest())
	{
		return Vector2<float>::Zero();
	}

	return m_velocity * p_mass;
}


PhysicMaterial* Rigidbody2D::GetPhysicMaterial() const
{
	return m_physicMaterial.get();
}

GameObject* Rigidbody2D::GetGameObject() const
{
	return m_gameObject;
}



void Rigidbody2D::MoveToPositionUpdating(const Vector2<float>& position)
{
	m_position = position;
	UpdateTransformPosition();
}

void Rigidbody2D::UpdateTransformPosition()
{
	m_gameObject->GetTransform()->p_worldPosition = m_position;
}



void Rigidbody2D::ApplyFriction(const float& deltaTime)
{
	if (IsAtRest())
	{
		ClearMovement();
		return;
	}

	m_acceleration -= m_moveDirection * (deltaTime * m_physicMaterial->GetFriction());
}

bool Rigidbody2D::IsAtRest() const
{
	return m_speed < 0.1f;
}

void Rigidbody2D::ClearMovement()
{
	m_acceleration = m_velocity = Vector2<float>::Zero();
	m_speed = 0.0f;
}



void Rigidbody2D::ApplyForce(const Vector2<float>& force)
{
	m_acceleration += ComputeForceAcceleration(force);
	SetVelocity(m_acceleration); // This might not be physically correct xd
}

Vector2<float> Rigidbody2D::ComputeGravityForceAcceleration(const Vector2<float>& gravityForce)
{
	return ComputeForceAcceleration(gravityForce) * p_gravityScale;
}

Vector2<float> Rigidbody2D::ComputeForceAcceleration(const Vector2<float>& force)
{
	return force / p_mass;
}


Vector2<float> Rigidbody2D::GetCurrentMotionForce()
{
	return m_acceleration * p_mass;
}



void Rigidbody2D::RefreshPosition()
{
	m_position = m_gameObject->GetTransform()->p_worldPosition;
}

