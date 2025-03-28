#pragma once
#include "PlayerThinkingState.h"


class PlayerThinkingState_Hitting : public PlayerThinkingState
{
public:
	PlayerThinkingState_Hitting(BilliardsPlayer* player);

	virtual bool Update() override;
	virtual void Exit() override;

protected:
	virtual void DoEnter() override;

};
