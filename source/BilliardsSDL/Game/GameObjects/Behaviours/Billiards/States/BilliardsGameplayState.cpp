#include "BilliardsGameplayState.h"


BilliardsGameplayState::BilliardsGameplayState(BilliardsGameplayStateBlackboard* blackboard)
	: m_nextState(Type::None), m_blackboard(blackboard)
{}

BilliardsGameplayState::~BilliardsGameplayState()
{}


void BilliardsGameplayState::Enter()
{
	SetNextState(Type::None);
	DoEnter();
}

BilliardsGameplayState::Type BilliardsGameplayState::GetNextState() const
{
	return m_nextState;
}

void BilliardsGameplayState::SetNextState(const Type& nextState)
{
	m_nextState = nextState;
}

BilliardsGameplayStateBlackboard* BilliardsGameplayState::GetBlackboard() const
{
	return m_blackboard;
}
