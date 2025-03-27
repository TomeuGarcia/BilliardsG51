#include "PlayerThinkingFSM.h"

PlayerThinkingFSM::PlayerThinkingFSM()
	: m_statesMap(), m_currentState(nullptr)
{}

PlayerThinkingFSM::~PlayerThinkingFSM()
{}

void PlayerThinkingFSM::Init()
{
	m_statesMap[PlayerThinkingState::Type::MovingAround] = PlayerThinkingState_MovingAround();
	m_statesMap[PlayerThinkingState::Type::PinnedToHit] = PlayerThinkingState_PinnedToHit();
	m_statesMap[PlayerThinkingState::Type::Hitting] = PlayerThinkingState_Hitting();
}


void PlayerThinkingFSM::Enter()
{
	m_currentState = &m_statesMap[PlayerThinkingState::Type::MovingAround];
	m_currentState->Enter();
}

bool PlayerThinkingFSM::Update()
{
	if (m_currentState->Update())
	{
		m_currentState->Exit();

		PlayerThinkingState::Type nextState = m_currentState->GetNextState();
		if (nextState == PlayerThinkingState::Type::Finished)
		{
			return true;
		}

		m_currentState = &m_statesMap[nextState];
		m_currentState->Enter();
	}

	return false;
}


void PlayerThinkingFSM::Exit()
{
	
}
