#include "GameFinishState_VictoryAnimation.h"



GameFinishState_VictoryAnimation::GameFinishState_VictoryAnimation(BilliardsGameplayStateBlackboard* blackboard)
	: GameFinishState(blackboard), m_transitionDelayTimer(1.5f)
{
}


void GameFinishState_VictoryAnimation::DoEnter()
{
	m_transitionDelayTimer.ClearTime();
}

bool GameFinishState_VictoryAnimation::Update()
{
	m_transitionDelayTimer.Update(GameTime::GetInstance()->GetDeltaTime());
	if (m_transitionDelayTimer.HasFinished())
	{
		SetNextState(Type::AskingWinnerName);
		return true;
	}

	return false;
}

void GameFinishState_VictoryAnimation::Exit()
{
}
