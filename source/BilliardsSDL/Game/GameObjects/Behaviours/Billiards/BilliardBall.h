#pragma once
#include <memory>
#include "../Behaviour.h"
#include "../../../Render/Renderers/Image/Image.h"
#include "../../../Render/Renderers/Text/Text.h"
#include "../../../Render/GameRenderManager.h"

#include "../../../Physics/Rigidbodies/Rigidbody2D.h"
#include "../../../Physics/Colliders/CircleCollider2D.h"

#include "../../../Systems/GameRandom.h"
#include "../../../Systems/GameSpacesComputer.h"
#include "../../../Systems/GameTweener.h"
#include "../../../Systems/GameDelayedCallScheduler.h"

#include "../../../Audio/SFXSound.h"


class BilliardBall : public Behaviour, public GameDelayedCallScheduler::ICallSource
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
	BilliardBall(const std::shared_ptr<CircleCollider2D>& collider, const std::shared_ptr<Rigidbody2D>& rigidbody, 
		const std::shared_ptr<Renderer> renderer, const ColorType& color, 
		const std::shared_ptr<SFXSound>& movedSound);
	~BilliardBall();

public:
	virtual void Start() override;
	virtual void OnDestroy() override;
	virtual void Update() override;

public:
	void SetPosition(const Vector2<float>& position);
	Transform* GetTransform() const;
	const ColorType GetColorType();

	const Circle& GetCollisionCircle();
	Renderer* GetRenderer() const;

	void SetIgnoringPhysics();
	void SetUsingPhysics();

	void ApplyForce(const Vector2<float>& force);
	bool IsMoving() const;
	float GetCurrentSpeed();

	void PlayEnterEnterHoleAnimation(const Vector2<float>& holeCenter);
	void PlayExitEnterHoleAnimation(const Vector2<float>& goalPosition, const float& moveDuration);

	void PlayMovedSound(const float& delay);


private:
	void UpdateRendererWithSpeed();

private:
	void DoPlayMovedSound();


private:
	std::shared_ptr<CircleCollider2D> m_collider;
	std::shared_ptr<Rigidbody2D> m_rigidbody;
	std::shared_ptr<Renderer> m_renderer;
	Vector2<float> m_startPosition;
	ColorType m_colorType;

	Vector2<float> m_originalScale;

	std::shared_ptr<SFXSound> m_movedSound;
};