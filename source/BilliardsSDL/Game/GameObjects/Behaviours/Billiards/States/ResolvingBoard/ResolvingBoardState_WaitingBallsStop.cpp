#include "ResolvingBoardState_WaitingBallsStop.h"




ResolvingBoardState_WaitingBallsStop::ResolvingBoardState_WaitingBallsStop(BilliardsGameplayStateBlackboard* blackboard)
	: ResolvingBoardState(blackboard)
{
}

ResolvingBoardState_WaitingBallsStop::~ResolvingBoardState_WaitingBallsStop()
{
}


void ResolvingBoardState_WaitingBallsStop::DoEnter()
{
}


bool ResolvingBoardState_WaitingBallsStop::Update()
{
	if (GetBlackboard()->GetSpecialEventsManager()->AllBallsStoppedMoving())
	{
		SetNextState(Type::ReturningMissplacedBalls);
		return true;
	}

	return false;
}

void ResolvingBoardState_WaitingBallsStop::Exit()
{
	GetBlackboard()->GetCurrentPlayer()->GetStick()->TweenToResting();
}

