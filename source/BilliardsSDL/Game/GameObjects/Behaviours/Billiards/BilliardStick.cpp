#include "BilliardStick.h"

BilliardStick::BilliardStick(Transform* transform, Image* image, 
	const Vector2<float>& defaultImageDirection, const float& stickDistanceToHandle, const float& stickDistanceToTip)
	: m_transform(transform), m_image(image), 
	m_defaultImageDirection(defaultImageDirection), 
	m_stickDistanceToHandle(stickDistanceToHandle), 
	m_stickDistanceToTip(stickDistanceToTip)
{
}

BilliardStick::~BilliardStick()
{
}

void BilliardStick::Start()
{
	m_restingPosition = m_transform->p_worldPosition;
}



void BilliardStick::SetTipPositionAndLookDirection(const Vector2<float>& tipPosition, const Vector2<float>& lookDirection)
{
	Vector2<float> position = tipPosition - (lookDirection * m_stickDistanceToTip);
	m_transform->p_worldPosition = position;

	float rotation = Math::Angle(m_defaultImageDirection, lookDirection) - 90.0f;
	m_image->p_rotationInDegrees = rotation;
}



void BilliardStick::SetResting()
{
	m_transform->p_worldPosition = m_restingPosition;
	m_image->p_rotationInDegrees = 0.0f;
}


