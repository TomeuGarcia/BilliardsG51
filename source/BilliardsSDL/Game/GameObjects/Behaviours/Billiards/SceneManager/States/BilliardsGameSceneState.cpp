#include "BilliardsGameSceneState.h"

void BilliardsGameSceneState::Enter()
{
	SetNextState(Type::None);
	DoEnter();
}

BilliardsGameSceneState::Type BilliardsGameSceneState::GetNextState() const
{
	return m_nextState;
}

void BilliardsGameSceneState::SetNextState(const Type& nextState)
{
	m_nextState = nextState;
}
