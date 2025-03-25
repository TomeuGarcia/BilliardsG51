#include "BilliardBall.h"


BilliardBall::BilliardBall(const std::shared_ptr<Rigidbody2D>& rigidbody)
	: m_rigidbody(rigidbody)
{
}

BilliardBall::~BilliardBall()
{
}

void BilliardBall::Start()
{
	const Vector2<float> force =
		GameRandom::GetInstance()->GetRandomUnitCircle() *
		GameRandom::GetInstance()->GetRandomFloat(2.0f, 5.0f);

	m_rigidbody.get()->ApplyForce(force);
}

void BilliardBall::Update()
{
	/*
	const Vector2<int> origin = GameSpacesComputer::GetInstance()->WorldToWindowPosition(Vector2<float>::Zero());
	const Vector2<int> current = GameSpacesComputer::GetInstance()->WorldToWindowPosition(
		m_rigidbody.get()->GetCollider()->GetGameObject()->GetTransform()->p_worldPosition);

	GameRenderManager::GetInstance()->DrawDebugLine(Colors::Red, origin, current);
	*/
}

void BilliardBall::SetPosition(const Vector2<float>& position)
{
	m_rigidbody.get()->GetGameObject()->GetTransform()->p_worldPosition = position;
}
