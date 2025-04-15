#include "BilliardsGameSceneState_Playing.h"

BilliardsGameSceneState_Playing::BilliardsGameSceneState_Playing(BilliardsGameplayStateBlackboard* gameplayBlackboard)
	: m_gameplayFSM()
{
	m_gameplayFSM.Init(gameplayBlackboard);
	m_gameplayFSM.Start();
}

BilliardsGameSceneState_Playing::~BilliardsGameSceneState_Playing()
{
	m_gameplayFSM.Finish();
}


void BilliardsGameSceneState_Playing::DoEnter()
{
}

bool BilliardsGameSceneState_Playing::Update()
{
	if (GameInput::GetInstance()->GetKeyDown(KeyCode::Esc) && CanPause())
	{
		SetNextState(BilliardsGameSceneState::Type::Paused);
		return true;
	}

	if (m_gameplayFSM.Update())
	{
		SetNextState(BilliardsGameSceneState::Type::Quit);
		return true;
	}

	return false;
}

void BilliardsGameSceneState_Playing::Exit()
{
}



bool BilliardsGameSceneState_Playing::CanPause() const
{
	const BilliardsGameplayState::Type currentState = m_gameplayFSM.GetCurrentStateType();

	return 
		currentState == BilliardsGameplayState::Type::PlacingBalls ||
		currentState == BilliardsGameplayState::Type::Thinking_Red ||
		currentState == BilliardsGameplayState::Type::Thinking_Blue ||
		currentState == BilliardsGameplayState::Type::ResolvingBoard;
}
