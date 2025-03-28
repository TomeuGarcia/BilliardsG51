#pragma once
#include "../BilliardsGameplayState.h"


class BilliardsGameplayState_GameFinish : public BilliardsGameplayState
{
public:
	BilliardsGameplayState_GameFinish(BilliardsGameplayStateBlackboard* blackboard);
	virtual ~BilliardsGameplayState_GameFinish();


	bool Update() override;
	void Exit() override;

protected:
	void DoEnter() override;

};