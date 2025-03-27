#pragma once
#include <unordered_map>
#include "PlayerThinkingState_MovingAround.h"
#include "PlayerThinkingState_PinnedToHit.h"
#include "PlayerThinkingState_Hitting.h"


class PlayerThinkingFSM
{
public:
	PlayerThinkingFSM();
	~PlayerThinkingFSM();

	void Init();

	void Enter();
	bool Update();
	void Exit();


private:
	std::unordered_map<PlayerThinkingState::Type, PlayerThinkingState> m_statesMap;
	PlayerThinkingState* m_currentState;

};