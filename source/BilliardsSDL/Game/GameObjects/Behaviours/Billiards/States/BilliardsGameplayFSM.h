#pragma once
#include "Init/BilliardsGameplayState_Init.h"
#include "PlacingBalls/BilliardsGameplayState_PlacingBalls.h"
#include "Thinking/BilliardsGameplayState_PlayerThinking.h"
#include "ResolvingBoard/BilliardsGameplayState_ResolvingBoard.h"
#include "GameFinish/BilliardsGameplayState_GameFinish.h"



class BilliardsGameplayFSM
{
public:
	BilliardsGameplayFSM();

	void Init(BilliardsGameplayStateBlackboard* gameplayStatesBlackboard);

	void Start();
	bool Update();
	void Finish();

	BilliardsGameplayState::Type GetCurrentStateType() const;

private:
	std::unordered_map<BilliardsGameplayState::Type, std::shared_ptr<BilliardsGameplayState>> m_gameplayStatesMap;
	BilliardsGameplayState* m_currentState;
	BilliardsGameplayState::Type m_currentStateType;
};