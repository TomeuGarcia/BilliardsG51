#include "GameFinishState_AskingWinnerName.h"

GameFinishState_AskingWinnerName::GameFinishState_AskingWinnerName(BilliardsGameplayStateBlackboard* blackboard)
	: GameFinishState(blackboard)
{
}



void GameFinishState_AskingWinnerName::DoEnter()
{   
    BilliardsPlayer* winnerPlayer = GetBlackboard()->GetWinnerPlayer();

    std::printf("\nWinner is %s, with: %i points!\n",
        winnerPlayer->GetName().c_str(),
        winnerPlayer->GetScore().GetCurrentValue());

    GetBlackboard()->GetSpecialEventsManager()->AskWinnerNameAndAddToRanking(winnerPlayer);
}

bool GameFinishState_AskingWinnerName::Update()
{
	SetNextState(Type::Finished);
	return true;
}

void GameFinishState_AskingWinnerName::Exit()
{
    system("cls");
}
