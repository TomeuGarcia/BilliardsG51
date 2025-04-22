#pragma once
#include "../Player/BilliardsPlayer.h"


class IPlayerScoresDisplay
{
public:
	virtual void Init(const std::vector<BilliardsPlayer*>& players) = 0;
	virtual void Cleanup() = 0;
	virtual void UpdateDisplayedScore() = 0;
};