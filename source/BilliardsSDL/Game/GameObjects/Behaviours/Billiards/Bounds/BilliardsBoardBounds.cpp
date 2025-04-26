#include "BilliardsBoardBounds.h"

BilliardsBoardBounds::BilliardsBoardBounds(IBilliardsBoardBoundsListener* listener)
	: m_listener(listener)
{
}


void BilliardsBoardBounds::OnTriggerExit(GameObject* other)
{
	BilliardBall* ball{ nullptr };
	if (other->TryGetBehaviour<BilliardBall>(ball))
	{
		m_listener->OnBallExitsBoardBounds(ball);
	}
}
