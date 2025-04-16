#include "Camera2D.h"

Camera2D::Camera2D()
	: m_worldPosition(Vector2<float>::Zero()), m_rotationAnglesInDegrees(0.0f)
{
}

Vector2<float> Camera2D::GetWorldPosition() const
{
	return m_worldPosition;
}

void Camera2D::SetWorldPosition(const Vector2<float>& worldPosition)
{
	m_worldPosition = worldPosition;
}

float Camera2D::GetRotationAnglesInDegrees() const
{
	return m_rotationAnglesInDegrees;
}

void Camera2D::SetrotationAngles(const float& rotationAnglesInDegrees)
{
	m_rotationAnglesInDegrees = rotationAnglesInDegrees;
}
