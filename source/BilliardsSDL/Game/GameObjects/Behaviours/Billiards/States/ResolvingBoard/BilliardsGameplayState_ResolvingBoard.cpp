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
}

bool BilliardsGameplayState_ResolvingBoard::Update()
{
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
}

