#pragma once
#include "BilliardsGameSceneState.h"
#include "../../States/BilliardsGameplayFSM.h"
#include "../../States/BilliardsGameplayStateBlackboard.h"


class BilliardsGameSceneState_Playing : public BilliardsGameSceneState
{
public:
	BilliardsGameSceneState_Playing(BilliardsGameplayStateBlackboard* gameplayBlackboard);
	~BilliardsGameSceneState_Playing();

	virtual bool Update() override;
	virtual void Exit() override;
protected:
	virtual void DoEnter() override;


private:
	bool CanPause() const;


private:
	BilliardsGameplayFSM m_gameplayFSM;
};