#include "BilliardsGameplayState_GameFinish.h"

BilliardsGameplayState_GameFinish::BilliardsGameplayState_GameFinish(BilliardsGameplayStateBlackboard* blackboard)
    : BilliardsGameplayState(blackboard), m_statesMap(), m_currentState(nullptr)
{
	m_statesMap[GameFinishState::Type::VictoryAnimation] = std::make_shared<GameFinishState_VictoryAnimation>(blackboard);
	m_statesMap[GameFinishState::Type::AskingWinnerName] = std::make_shared<GameFinishState_AskingWinnerName>(blackboard);
}

BilliardsGameplayState_GameFinish::~BilliardsGameplayState_GameFinish()
{
}



void BilliardsGameplayState_GameFinish::DoEnter()
{
    GetBlackboard()->SetWinnerPlayer(GetBlackboard()->GetCurrentPlayer());
    GetBlackboard()->GetSpecialEventsManager()->OnGameFinishStart();

    m_currentState = m_statesMap[GameFinishState::Type::VictoryAnimation].get();
    m_currentState->Enter();
}



bool BilliardsGameplayState_GameFinish::Update()
{
    if (m_currentState->Update())
    {
        m_currentState->Exit();

        const GameFinishState::Type nextState = m_currentState->GetNextState();
        if (nextState == GameFinishState::Type::Finished)
        {
            m_currentState = nullptr;
            SetNextState(Type::GameQuit);
            return true;
        }
        else
        {
            m_currentState = m_statesMap[nextState].get();
            m_currentState->Enter();
        }              
    }


    return false;
}

void BilliardsGameplayState_GameFinish::Exit()
{
    if (m_currentState != nullptr)
    {
        m_currentState->Exit();
        m_currentState = nullptr;
    }    
}

