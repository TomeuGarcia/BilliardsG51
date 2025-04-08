#include "BilliardBall.h"


BilliardBall::BilliardBall(const std::shared_ptr<CircleCollider2D>& collider, const std::shared_ptr<Rigidbody2D>& rigidbody, 
	const std::shared_ptr<Renderer> renderer, const ColorType& color)
	: m_collider(collider), m_rigidbody(rigidbody), m_renderer(renderer), m_colorType(color)
{
}


BilliardBall::~BilliardBall()
{
}

void BilliardBall::Start()
{
	m_startPosition = m_rigidbody->GetGameObject()->GetTransform()->p_worldPosition;
	p_originalScale = m_renderer->p_scale;
}

void BilliardBall::Update()
{
	UpdateRendererWithSpeed();
}

void BilliardBall::SetPosition(const Vector2<float>& position)
{
	m_rigidbody->MoveToPosition(position);
}

Transform* BilliardBall::GetTransform() const
{
	return m_rigidbody->GetGameObject()->GetTransform();
}

const BilliardBall::ColorType BilliardBall::GetColorType()
{
	return m_colorType;
}

const Circle& BilliardBall::GetCollisionCircle()
{
	return m_collider->GetShape();
}

Renderer* BilliardBall::GetRenderer() const
{
	return m_renderer.get();
}


void BilliardBall::SetIgnoringPhysics()
{
	m_rigidbody->SetIsEnabled(false);
	m_rigidbody->ClearMovement();
}

void BilliardBall::SetUsingPhysics()
{
	m_rigidbody->SetIsEnabled(true);		
}

void BilliardBall::ApplyForce(const Vector2<float>& force)
{
	m_rigidbody->ApplyForce(force);
}

bool BilliardBall::IsMoving() const
{
	return !m_rigidbody->IsAtRest();
}

float BilliardBall::GetCurrentSpeed()
{
	return m_rigidbody->GetSpeed();
}




void BilliardBall::PlayEnterEnterHoleAnimation(const Vector2<float>& holeCenter)
{
	const float moveToHoleDuration = Math::Clamp(Vector2<float>::Distance(holeCenter, GetTransform()->p_worldPosition) / (GetCurrentSpeed() * 0.2f), 0.1f, 0.5f);

	GameTweener::GetInstance()->TweenPosition(GetTransform(), holeCenter, moveToHoleDuration, 0.0f);
	GameTweener::GetInstance()->TweenColor(GetRenderer(), Colors::Transparent, moveToHoleDuration, moveToHoleDuration / 2.0f);
}

void BilliardBall::PlayExitEnterHoleAnimation(const Vector2<float>& goalPosition, const float& moveDuration)
{
	GameTweener::GetInstance()->CompleteColor(GetRenderer());	

	GameTweener::GetInstance()->TweenColor(GetRenderer(), Colors::White, moveDuration, 0.0f);
	GameTweener::GetInstance()->TweenPosition(GetTransform(), goalPosition, moveDuration, moveDuration / 2.0f);
}



void BilliardBall::UpdateRendererWithSpeed()
{
	if (m_rigidbody->IsAtRest())
	{
		m_renderer->p_scale = p_originalScale;
		return;
	}

	const float speedFactor = m_rigidbody->GetSpeed() / 80.0f;
	const float xScale = 1.0f - Math::Min(0.15f, speedFactor);
	const float yScale = 1.0f + Math::Min(0.05f, speedFactor);
	m_renderer->p_scale.x = p_originalScale.x * xScale;
	m_renderer->p_scale.y = p_originalScale.y * yScale;

	const float rotation = Math::Angle(Vector2<float>::Right(), m_rigidbody->GetVelocity().Normalized());
	m_renderer->p_rotationInDegrees = rotation;
}
