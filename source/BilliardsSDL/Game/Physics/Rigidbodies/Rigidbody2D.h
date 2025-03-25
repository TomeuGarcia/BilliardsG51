#pragma once
#include "../../../Shared/Types/Vector2/Vector2.h"
#include "../../GameObjects/GameObject.h"
#include "PhysicMaterial.h"
#include "../Colliders/Collider2D.h"


class Rigidbody2D
{
public:
	Rigidbody2D(const std::shared_ptr<Collider2D>& collider,
				const std::shared_ptr<PhysicMaterial>& physicMaterial,
				const float& mass, const float& gravityScale);
	~Rigidbody2D();

	Vector2<float> GetAcceleration() const;
	PhysicMaterial* GetPhysicMaterial() const;
	Collider2D* GetCollider() const;

	void UpdatePosition();
	void ApplyFriction();

	void ApplyForce(const Vector2<float>& force);
	Vector2<float> ComputeGravityForceAcceleration(const Vector2<float>& gravityForce);

private:
	Vector2<float> ComputeForceAcceleration(const Vector2<float>& force);


public:
	Vector2<float> p_position;
	Vector2<float> p_velocity;
	float p_mass;
	float p_gravityScale;

private:
	Vector2<float> m_acceleration;
	Vector2<float> m_deceleration;
	std::shared_ptr<PhysicMaterial> m_physicMaterial;
	std::shared_ptr<Collider2D> m_collider;
};