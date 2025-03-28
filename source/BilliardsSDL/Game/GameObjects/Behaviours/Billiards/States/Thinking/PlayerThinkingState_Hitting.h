#pragma once
#include "PlayerThinkingState.h"


class PlayerThinkingState_Hitting : public PlayerThinkingState
{
public:
	PlayerThinkingState_Hitting(BilliardsGameplayStateBlackboard* blackboard, BilliardsPlayer* player);

	virtual bool Update() override;
	virtual void Exit() override;

protected:
	virtual void DoEnter() override;


private:
	bool TryHitBalls();

private:
	Timer m_tweenWaitTimer;
};
