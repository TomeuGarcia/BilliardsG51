#include "BilliardsGameplayState_PlayerThinking.h"



BilliardsGameplayState_PlayerThinking::BilliardsGameplayState_PlayerThinking(BilliardsGameplayStateBlackboard* blackboard, BilliardsPlayer* player)
	: BilliardsGameplayState(blackboard), m_statesMap(), m_currentState(nullptr)
{
	m_statesMap[PlayerThinkingState::Type::MovingAround] = std::make_shared<PlayerThinkingState_MovingAround>(player);
	m_statesMap[PlayerThinkingState::Type::PinnedToHit] = std::make_shared<PlayerThinkingState_PinnedToHit>(player);
	m_statesMap[PlayerThinkingState::Type::Hitting] = std::make_shared<PlayerThinkingState_Hitting>(player);
}

BilliardsGameplayState_PlayerThinking::~BilliardsGameplayState_PlayerThinking()
{}



void BilliardsGameplayState_PlayerThinking::DoEnter()
{
	m_currentState = (m_statesMap[PlayerThinkingState::Type::MovingAround]).get();
	m_currentState->Enter();
}


bool BilliardsGameplayState_PlayerThinking::Update()
{
	if (m_currentState->Update())
	{
		m_currentState->Exit();

		PlayerThinkingState::Type nextState = m_currentState->GetNextState();
		if (nextState == PlayerThinkingState::Type::Finished)
		{
			m_currentState = nullptr;
			return true;
		}

		m_currentState = (m_statesMap[nextState]).get();
		m_currentState->Enter();
	}

	return false;
}

void BilliardsGameplayState_PlayerThinking::Exit()
{
	if (m_currentState != nullptr)
	{
		m_currentState->Exit();
	}
}

