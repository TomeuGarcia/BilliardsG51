#include "PlayerThinkingState_Hitting.h"


PlayerThinkingState_Hitting::PlayerThinkingState_Hitting(BilliardsPlayer* player)
	: PlayerThinkingState(player)
{
}

void PlayerThinkingState_Hitting::DoEnter()
{}

bool PlayerThinkingState_Hitting::Update()
{
	return false;
}

void PlayerThinkingState_Hitting::Exit()
{}

