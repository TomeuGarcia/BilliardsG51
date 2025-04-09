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
    BilliardsPlayer* winnerPlayer = GetBlackboard()->GetCurrentPlayer();

    std::printf("\nWinner is %s, with: %i points!\n",
        winnerPlayer->GetName().c_str(),
        winnerPlayer->GetScore().GetCurrentValue());

    GetBlackboard()->GetSpecialEventsManager()->AskWinnerNameAndAddToRanking(winnerPlayer);
}



bool BilliardsGameplayState_GameFinish::Update()
{
    SetNextState(Type::GameQuit);
    return true;
}

void BilliardsGameplayState_GameFinish::Exit()
{
    system("cls");
}

