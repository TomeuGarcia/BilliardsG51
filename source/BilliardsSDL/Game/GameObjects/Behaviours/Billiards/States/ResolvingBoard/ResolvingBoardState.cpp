#include "ResolvingBoardState.h"

ResolvingBoardState::ResolvingBoardState(BilliardsGameplayStateBlackboard* blackboard)
	: m_blackboard(blackboard), m_nextState(Type::None)
{
}

void ResolvingBoardState::Enter()
{
	SetNextState(Type::None);
	DoEnter();
}

ResolvingBoardState::Type ResolvingBoardState::GetNextState() const
{
	return m_nextState;
}

void ResolvingBoardState::SetNextState(const Type& nextState)
{
	m_nextState = nextState;
}

BilliardsGameplayStateBlackboard* ResolvingBoardState::GetBlackboard() const
{
	return m_blackboard;
}
