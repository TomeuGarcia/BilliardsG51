#pragma once
#include <unordered_map>

#include "../BilliardsGameplayState.h"

#include "ResolvingBoardState_ReturningMissplacedBalls.h"
#include "ResolvingBoardState_WaitingBallsStop.h"



class BilliardsGameplayState_ResolvingBoard : public BilliardsGameplayState
{
public:
	BilliardsGameplayState_ResolvingBoard(BilliardsGameplayStateBlackboard* blackboard);
	virtual ~BilliardsGameplayState_ResolvingBoard();


	bool Update() override;
	void Exit() override;

protected:
	void DoEnter() override;


private:
	std::unordered_map<ResolvingBoardState::Type, std::shared_ptr<ResolvingBoardState>> m_statesMap;
	ResolvingBoardState* m_currentState;

	Type m_keepPlayerNextStateType; 
	Type m_changePlayerNextStateType;
};
