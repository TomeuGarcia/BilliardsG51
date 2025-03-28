#include "BilliardsGameplayState_ResolvingBoard.h"

BilliardsGameplayState_ResolvingBoard::BilliardsGameplayState_ResolvingBoard(BilliardsGameplayStateBlackboard* blackboard)
    : BilliardsGameplayState(blackboard)
{
}

BilliardsGameplayState_ResolvingBoard::~BilliardsGameplayState_ResolvingBoard()
{
}



void BilliardsGameplayState_ResolvingBoard::DoEnter()
{
    m_previousPlayer = GetBlackboard()->GetCurrentPlayer();
}

bool BilliardsGameplayState_ResolvingBoard::Update()
{
    if (!GetBlackboard()->GetSpecialEventsManager()->AllBallsStoppedMoving())
    {
        return false;
    }


    m_changingPlayer = true;
    if (GetBlackboard()->GetCurrentPlayer() == GetBlackboard()->GetPlayerRed())
    {
        SetNextState(Type::Thinking_Blue);
        return true;
    }
    else
    {
        SetNextState(Type::Thinking_Red);
        return true;
    }

    return false;
}

void BilliardsGameplayState_ResolvingBoard::Exit()
{
    if (m_changingPlayer)
    {
        m_previousPlayer->GetStick()->TweenToResting();
    }
}

