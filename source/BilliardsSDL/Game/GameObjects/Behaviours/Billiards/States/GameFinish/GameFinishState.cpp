#include "GameFinishState.h"

GameFinishState::GameFinishState(BilliardsGameplayStateBlackboard* blackboard)
	: m_blackboard(blackboard), m_nextState(Type::None)
{
}

void GameFinishState::Enter()
{
	SetNextState(Type::None);
	DoEnter();
}

GameFinishState::Type GameFinishState::GetNextState() const
{
	return m_nextState;
}

void GameFinishState::SetNextState(const Type& nextState)
{
	m_nextState = nextState;
}

BilliardsGameplayStateBlackboard* GameFinishState::GetBlackboard() const
{
	return m_blackboard;
}