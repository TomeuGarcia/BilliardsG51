#include "PhysicMaterial.h"

PhysicMaterial::PhysicMaterial(const float& bounciness, const float& friction)
{
	SetBounciness(bounciness);
	SetFriction(friction);
}

PhysicMaterial::~PhysicMaterial()
{
}

float PhysicMaterial::GetBounciness() const
{
	return m_bounciness;
}

float PhysicMaterial::GetFriction() const
{
	return m_friction;
}

void PhysicMaterial::SetBounciness(const float& bounciness)
{
	m_bounciness = Math::Clamp01(bounciness);
}

void PhysicMaterial::SetFriction(const float& friction)
{
	m_friction = Math::Max(0, friction);
}
