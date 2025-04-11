#pragma once
#include "GameFinishState.h"

class GameFinishState_VictoryAnimation : public GameFinishState
{
public:
	GameFinishState_VictoryAnimation(BilliardsGameplayStateBlackboard* blackboard);

public:
	bool Update() override;
	void Exit() override;

protected:
	void DoEnter() override;


private:
	Timer m_transitionDelayTimer;
};