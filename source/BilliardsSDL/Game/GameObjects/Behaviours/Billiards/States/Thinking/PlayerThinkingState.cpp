#include "PlayerThinkingState.h"


PlayerThinkingState::PlayerThinkingState(BilliardsPlayer* player)
	: m_player(player)
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



BilliardsPlayer* PlayerThinkingState::GetPlayer() const
{
	return m_player;
}
