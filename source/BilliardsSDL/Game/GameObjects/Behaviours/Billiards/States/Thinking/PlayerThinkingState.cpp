#include "PlayerThinkingState.h"


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
