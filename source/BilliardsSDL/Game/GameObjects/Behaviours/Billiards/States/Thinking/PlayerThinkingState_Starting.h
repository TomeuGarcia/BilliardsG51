#pragma once
#include "PlayerThinkingState.h"


class PlayerThinkingState_Starting : public PlayerThinkingState
{
public:
	PlayerThinkingState_Starting(BilliardsGameplayStateBlackboard* blackboard, BilliardsPlayer* player);

	virtual bool Update() override;
	virtual void Exit() override;

protected:
	virtual void DoEnter() override;


private:
	Timer m_transitionTimer;
	Color m_startingColor;

};



