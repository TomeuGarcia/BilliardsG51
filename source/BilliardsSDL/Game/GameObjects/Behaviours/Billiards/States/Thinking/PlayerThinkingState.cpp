#include "PlayerThinkingState.h"


PlayerThinkingState::PlayerThinkingState(BilliardsGameplayStateBlackboard* blackboard, BilliardsPlayer* player)
	: m_blackboard(blackboard), m_player(player), m_nextState(Type::None)
{
}

void PlayerThinkingState::Enter()
{
	SetNextState(Type::None);
	DoEnter();
}

PlayerThinkingState::Type PlayerThinkingState::GetNextState() const
{
	return m_nextState;
}

void PlayerThinkingState::SetNextState(const Type& nextState)
{
	m_nextState = nextState;
}



BilliardsGameplayStateBlackboard* PlayerThinkingState::GetBlackboard() const
{
	return m_blackboard;
}

BilliardsPlayer* PlayerThinkingState::GetPlayer() const
{
	return m_player;
}
