#include "BilliardsGameplayFSM.h"

BilliardsGameplayFSM::BilliardsGameplayFSM()
	: m_gameplayStatesMap(), m_currentState(nullptr), m_currentStateType(BilliardsGameplayState::Type::None)
{
}

void BilliardsGameplayFSM::Init(BilliardsGameplayStateBlackboard* gameplayStatesBlackboard)
{
	m_gameplayStatesMap[BilliardsGameplayState::Type::Init] =
		std::make_shared<BilliardsGameplayState_Init>(gameplayStatesBlackboard);

	m_gameplayStatesMap[BilliardsGameplayState::Type::PlacingBalls] =
		std::make_shared<BilliardsGameplayState_PlacingBalls>(gameplayStatesBlackboard);

	m_gameplayStatesMap[BilliardsGameplayState::Type::Thinking_Red] =
		std::make_shared<BilliardsGameplayState_PlayerThinking>(gameplayStatesBlackboard, gameplayStatesBlackboard->GetPlayerRed());

	m_gameplayStatesMap[BilliardsGameplayState::Type::Thinking_Blue] =
		std::make_shared<BilliardsGameplayState_PlayerThinking>(gameplayStatesBlackboard, gameplayStatesBlackboard->GetPlayerBlue());

	m_gameplayStatesMap[BilliardsGameplayState::Type::ResolvingBoard] =
		std::make_shared<BilliardsGameplayState_ResolvingBoard>(gameplayStatesBlackboard);

	m_gameplayStatesMap[BilliardsGameplayState::Type::GameFinish] =
		std::make_shared<BilliardsGameplayState_GameFinish>(gameplayStatesBlackboard);
}

void BilliardsGameplayFSM::Start()
{
	m_currentState = (m_gameplayStatesMap[BilliardsGameplayState::Type::Init]).get();
	m_currentState->Enter();
}

bool BilliardsGameplayFSM::Update()
{
	if (m_currentState->Update())
	{
		m_currentState->Exit();

		const BilliardsGameplayState::Type nextState = m_currentState->GetNextState();
		m_currentStateType = nextState;

		if (nextState == BilliardsGameplayState::Type::GameQuit)
		{
			return true;
		}

		m_currentState = (m_gameplayStatesMap[nextState]).get();
		m_currentState->Enter();
	}

	return false;
}

void BilliardsGameplayFSM::Finish()
{
	m_currentState->Exit();
}

BilliardsGameplayState::Type BilliardsGameplayFSM::GetCurrentStateType() const
{
	return m_currentStateType;
}
