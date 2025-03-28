#pragma once
#include "../BilliardsGameplayState.h"


class BilliardsGameplayState_Init : public BilliardsGameplayState
{
public:
	BilliardsGameplayState_Init(BilliardsGameplayStateBlackboard* blackboard);
	virtual ~BilliardsGameplayState_Init();

	bool Update() override;
	void Exit() override;

protected:
	void DoEnter() override;
};