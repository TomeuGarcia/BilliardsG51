#pragma once
#include <unordered_map>
#include "../BilliardsGameplayState.h"

#include "PlayerThinkingState_Starting.h"
#include "PlayerThinkingState_MovingAround.h"
#include "PlayerThinkingState_PinnedToHit.h"
#include "PlayerThinkingState_Hitting.h"



class BilliardsGameplayState_PlayerThinking : public BilliardsGameplayState
{
public:
	BilliardsGameplayState_PlayerThinking(BilliardsGameplayStateBlackboard* blackboard, BilliardsPlayer* player);
	virtual ~BilliardsGameplayState_PlayerThinking();
	

	bool Update() override;
	void Exit() override;

protected:
	void DoEnter() override;


private:
	std::unordered_map<PlayerThinkingState::Type, std::shared_ptr<PlayerThinkingState>> m_statesMap;
	PlayerThinkingState* m_currentState;
};