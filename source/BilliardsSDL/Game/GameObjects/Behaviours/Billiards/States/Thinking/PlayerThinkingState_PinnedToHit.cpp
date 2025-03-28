#include "PlayerThinkingState_PinnedToHit.h"


PlayerThinkingState_PinnedToHit::PlayerThinkingState_PinnedToHit(BilliardsPlayer* player)
	: PlayerThinkingState(player)
{
}

void PlayerThinkingState_PinnedToHit::DoEnter()
{}

bool PlayerThinkingState_PinnedToHit::Update()
{
	return false;
}

void PlayerThinkingState_PinnedToHit::Exit()
{}
