#include "BilliardsGameplayState_GameFinish.h"

BilliardsGameplayState_GameFinish::BilliardsGameplayState_GameFinish(BilliardsGameplayStateBlackboard* blackboard)
    : BilliardsGameplayState(blackboard)
{
}

BilliardsGameplayState_GameFinish::~BilliardsGameplayState_GameFinish()
{
}



void BilliardsGameplayState_GameFinish::DoEnter()
{
    printf("Winner is %s, with: %i points!\n",
        GetBlackboard()->GetCurrentPlayer()->GetName().c_str(),
        GetBlackboard()->GetCurrentPlayer()->GetScore().GetCurrentValue());
}

bool BilliardsGameplayState_GameFinish::Update()
{
    return false;
}

void BilliardsGameplayState_GameFinish::Exit()
{
    system("cls");
}

