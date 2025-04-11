#pragma once
#include "GameFinishState.h"


class GameFinishState_AskingWinnerName : public GameFinishState
{
public:
	GameFinishState_AskingWinnerName(BilliardsGameplayStateBlackboard* blackboard);

public:
	bool Update() override;
	void Exit() override;

protected:
	void DoEnter() override;
};

