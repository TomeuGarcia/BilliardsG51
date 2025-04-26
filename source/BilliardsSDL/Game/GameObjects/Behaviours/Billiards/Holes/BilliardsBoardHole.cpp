#include "BilliardsBoardHole.h"

BilliardsBoardHole::BilliardsBoardHole(Transform* transform, IBilliardBoardHoleInteractionsManager* interactionManager)
	: m_transform(transform), m_interactionManager(interactionManager)
{}

BilliardsBoardHole::~BilliardsBoardHole()
{}


void BilliardsBoardHole::OnTriggerEnter(GameObject* other)
{
	BilliardBall* ball{ nullptr };
	if (other->TryGetBehaviour<BilliardBall>(ball))
	{
		m_interactionManager->OnBallEnteredHole(ball, m_transform->p_worldPosition);
	}
}
