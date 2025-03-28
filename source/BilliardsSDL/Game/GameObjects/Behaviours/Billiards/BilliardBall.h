#pragma once
#include <memory>
#include "../Behaviour.h"
#include "../../../Render/Renderers/Image/Image.h"
#include "../../../Render/Renderers/Text/Text.h"
#include "../../../Physics/Rigidbodies/Rigidbody2D.h"
#include "../../../Systems/GameRandom.h"
#include "../../../Systems/GameSpacesComputer.h"
#include "../../../Render/GameRenderManager.h"
#include "../../../Physics/Colliders/CircleCollider2D.h"



class BilliardBall : public Behaviour
{
public:
	enum class ColorType
	{
		White,
		Black,
		Red,
		Blue,
	};

public:
	BilliardBall(const std::shared_ptr<CircleCollider2D>& collider, const std::shared_ptr<Rigidbody2D>& rigidbody, const ColorType& color);
	~BilliardBall();

public:
	virtual void Start() override;
	virtual void Update() override;

public:
	void SetPosition(const Vector2<float>& position);
	Transform* GetTransform() const;
	const ColorType GetColorType();

	const Circle& GetCollisionCircle();


	void SetIgnoringPhysics();
	void SetUsingPhysics();

	void ApplyForce(const Vector2<float>& force);

	bool IsMoving() const;

	float GetCurrentSpeed();


private:
	std::shared_ptr<CircleCollider2D> m_collider;
	std::shared_ptr<Rigidbody2D> m_rigidbody;
	Vector2<float> m_startPosition;
	ColorType m_colorType;
};