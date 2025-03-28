#pragma once
#include "../BilliardsGameplayState.h"



class BilliardsGameplayState_ResolvingBoard : public BilliardsGameplayState
{
public:
	BilliardsGameplayState_ResolvingBoard(BilliardsGameplayStateBlackboard* blackboard);
	virtual ~BilliardsGameplayState_ResolvingBoard();


	bool Update() override;
	void Exit() override;

protected:
	void DoEnter() override;

};
