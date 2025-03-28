#pragma once
#include "PlayerThinkingState.h"


class PlayerThinkingState_PinnedToHit : public PlayerThinkingState
{
public:
	PlayerThinkingState_PinnedToHit(BilliardsPlayer* player);

	virtual bool Update() override;
	virtual void Exit() override;

protected:
	virtual void DoEnter() override;

};
