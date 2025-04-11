#include "BilliardsGameplayState_ResolvingBoard.h"

BilliardsGameplayState_ResolvingBoard::BilliardsGameplayState_ResolvingBoard(BilliardsGameplayStateBlackboard* blackboard)
    : BilliardsGameplayState(blackboard), m_statesMap(), m_currentState(nullptr),
    m_keepPlayerNextStateType(Type::None), m_changePlayerNextStateType(Type::None)
{

    m_statesMap[ResolvingBoardState::Type::WaitingBallsStop] = std::make_shared<ResolvingBoardState_WaitingBallsStop>(blackboard);
    m_statesMap[ResolvingBoardState::Type::ReturningMissplacedBalls] = std::make_shared<ResolvingBoardState_ReturningMissplacedBalls>(blackboard);
}

BilliardsGameplayState_ResolvingBoard::~BilliardsGameplayState_ResolvingBoard()
{
}



void BilliardsGameplayState_ResolvingBoard::DoEnter()
{
    if (GetBlackboard()->GetCurrentPlayer() == GetBlackboard()->GetPlayerRed())
    {
        m_keepPlayerNextStateType = Type::Thinking_Red;
        m_changePlayerNextStateType = Type::Thinking_Blue;
    }
    else
    {
        m_keepPlayerNextStateType = Type::Thinking_Blue;
        m_changePlayerNextStateType = Type::Thinking_Red;
    }
    
    m_currentState = (m_statesMap[ResolvingBoardState::Type::WaitingBallsStop]).get();
}

bool BilliardsGameplayState_ResolvingBoard::Update()
{
    if (m_currentState->Update())
    {
        m_currentState->Exit();
        const ResolvingBoardState::Type nextState = m_currentState->GetNextState();

        if (nextState == ResolvingBoardState::Type::KeepPlayer)
        {
            SetNextState(m_keepPlayerNextStateType);
            m_currentState = nullptr;
            return true;
        }
        else if (nextState == ResolvingBoardState::Type::ChangePlayer)
        {
            GetBlackboard()->GetSpecialEventsManager()->OnPlayerStartsPlaying();
            SetNextState(m_changePlayerNextStateType);
            m_currentState = nullptr;
            return true;
        }
        else if (nextState == ResolvingBoardState::Type::PlayerVictory)
        {
            SetNextState(Type::GameFinish);
            m_currentState = nullptr;
            return true;
        }

        m_currentState = m_statesMap[nextState].get();
        m_currentState->Enter();
    }

    return false;
}

void BilliardsGameplayState_ResolvingBoard::Exit()
{
    if (m_currentState != nullptr)
    {
        m_currentState->Exit();
    }
}

