#pragma once
#include <unordered_map>
#include "../BilliardsGameplayState.h"
#include "GameFinishState_VictoryAnimation.h"
#include "GameFinishState_AskingWinnerName.h"


class BilliardsGameplayState_GameFinish : public BilliardsGameplayState
{
public:
	BilliardsGameplayState_GameFinish(BilliardsGameplayStateBlackboard* blackboard);
	virtual ~BilliardsGameplayState_GameFinish();


	bool Update() override;
	void Exit() override;

protected:
	void DoEnter() override;


private:
	std::unordered_map<GameFinishState::Type, std::shared_ptr<GameFinishState>> m_statesMap;
	GameFinishState* m_currentState;
};