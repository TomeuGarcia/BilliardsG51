#include "BilliardsBoardBounds.h"

BilliardsBoardBounds::BilliardsBoardBounds(IBilliardsBoardBoundsListener* listener)
	: m_listener(listener)
{
}


void BilliardsBoardBounds::OnTriggerExit(GameObject* other)
{
	const std::vector<std::shared_ptr<Behaviour>>& otherBehaviours = other->GetBehaviours();
	for (auto it = otherBehaviours.begin(); it != otherBehaviours.end(); ++it)
	{
		BilliardBall* ball = dynamic_cast<BilliardBall*>(it->get());
		if (ball != nullptr)
		{
			m_listener->OnBallExitsBoardBounds(ball);
			return;
		}
	}
}
