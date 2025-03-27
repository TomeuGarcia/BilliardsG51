#pragma once
#include "PlayerThinkingState.h"


class PlayerThinkingState_PinnedToHit : public PlayerThinkingState
{

public:
	virtual bool Update() override;
	virtual void Exit() override;

protected:
	virtual void DoEnter() override;

};
