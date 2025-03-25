#pragma once
#include "../../../Shared/Math/Math.h"

struct PhysicMaterial
{
public:
	PhysicMaterial(const float& bounciness, const float& friction);
	~PhysicMaterial();

	float GetBounciness() const;
	float GetFriction() const;

	void SetBounciness(const float& bounciness);
	void SetFriction(const float& friction);


private:
	float m_bounciness;
	float m_friction;
};