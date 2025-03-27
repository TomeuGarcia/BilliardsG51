#pragma once
#include "../../../Shared/Types/Vector2/Vector2.h"
#include "../../GameObjects/GameObject.h"
#include "PhysicMaterial.h"


class Rigidbody2D
{
public:
	Rigidbody2D(GameObject* gameObject,
				const std::shared_ptr<PhysicMaterial>& physicMaterial,
				const float& mass, const float& gravityScale);
	~Rigidbody2D();

	const Vector2<float>& GetVelocity() const;
	void SetVelocity(const Vector2<float>& velocity);

	const Vector2<float>& GetAcceleration() const;
	void SetAcceleration(const Vector2<float>& acceleration);

	PhysicMaterial* GetPhysicMaterial() const;
	GameObject* GetGameObject() const;

	void UpdatePosition();
	void ApplyFriction(const float& deltaTime);

	bool IsAtRest() const;
	void ClearMovement();

	void ApplyForce(const Vector2<float>& force);
	Vector2<float> ComputeGravityForceAcceleration(const Vector2<float>& gravityForce);

	Vector2<float> GetCurrentMotionForce();

private:
	Vector2<float> ComputeForceAcceleration(const Vector2<float>& force);


public:
	Vector2<float> p_position;
	float p_mass;
	float p_gravityScale;

private:	
	Vector2<float> m_velocity;
	Vector2<float> m_acceleration;
	float m_speed;

	std::shared_ptr<PhysicMaterial> m_physicMaterial;
	GameObject* m_gameObject;
};