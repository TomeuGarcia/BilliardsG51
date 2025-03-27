#pragma once
#include "PlayerThinkingState.h"


class PlayerThinkingState_Hitting : public PlayerThinkingState
{

public:
	virtual bool Update() override;
	virtual void Exit() override;

protected:
	virtual void DoEnter() override;

};
