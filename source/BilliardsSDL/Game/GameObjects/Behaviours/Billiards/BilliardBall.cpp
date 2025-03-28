#include "BilliardBall.h"


BilliardBall::BilliardBall(const std::shared_ptr<CircleCollider2D>& collider, const std::shared_ptr<Rigidbody2D>& rigidbody, 
	const ColorType& color)
	: m_collider(collider), m_rigidbody(rigidbody), m_colorType(color)
{
}


BilliardBall::~BilliardBall()
{
}

void BilliardBall::Start()
{
	m_startPosition = m_rigidbody->GetGameObject()->GetTransform()->p_worldPosition;

	/*
	const Vector2<float> force =
		GameRandom::GetInstance()->GetRandomUnitCircle() *
		GameRandom::GetInstance()->GetRandomFloat(7.0f, 9.0f);
		

	//const Vector2<float> force = m_startPosition * -2;
	
	m_rigidbody.get()->ApplyForce(force);
	*/
}

void BilliardBall::Update()
{
	/*
	const Vector2<int> current = GameSpacesComputer::GetInstance()->WorldToWindowPosition(
		m_rigidbody->GetGameObject()->GetTransform()->p_worldPosition);
	const Vector2<int> velocity = current + GameSpacesComputer::GetInstance()->WorldToWindowVector(m_rigidbody->GetVelocity());

	GameRenderManager::GetInstance()->DrawDebugLine(Colors::Cyan, current, velocity);
	*/
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


void BilliardBall::SetIgnoringPhysics()
{
	m_rigidbody->SetIsEnabled(false);
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

