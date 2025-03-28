#pragma once
#include "ResolvingBoardState.h"


class ResolvingBoardState_WaitingBallsStop : public ResolvingBoardState
{
public:
	ResolvingBoardState_WaitingBallsStop(BilliardsGameplayStateBlackboard* blackboard);
	~ResolvingBoardState_WaitingBallsStop();


	bool Update() override;
	void Exit() override;

protected:
	void DoEnter() override;
};