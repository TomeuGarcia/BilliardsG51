#include "BilliardsBoardHole.h"

BilliardsBoardHole::BilliardsBoardHole(Transform* transform, IBilliardBoardHoleInteractionsManager* interactionManager)
	: m_transform(transform), m_interactionManager(interactionManager)
{}

BilliardsBoardHole::~BilliardsBoardHole()
{}


void BilliardsBoardHole::OnTriggerEnter(GameObject* other)
{
	const std::vector<std::shared_ptr<Behaviour>>& otherBehaviours = other->GetBehaviours();
	for (auto it = otherBehaviours.begin(); it != otherBehaviours.end(); ++it)
	{
		BilliardBall* ball = dynamic_cast<BilliardBall*>(it->get());
		if (ball != nullptr)
		{
			m_interactionManager->OnBallEnteredHole(ball, m_transform->p_worldPosition);
			return;
		}
	}
}
