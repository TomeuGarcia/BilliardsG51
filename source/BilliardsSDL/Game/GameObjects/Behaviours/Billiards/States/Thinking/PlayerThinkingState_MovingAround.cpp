#include "PlayerThinkingState_MovingAround.h"


PlayerThinkingState_MovingAround::PlayerThinkingState_MovingAround(BilliardsPlayer* player)
	: PlayerThinkingState(player)
{
}

void PlayerThinkingState_MovingAround::DoEnter()
{}

bool PlayerThinkingState_MovingAround::Update()
{
	return false;
}

void PlayerThinkingState_MovingAround::Exit()
{}
