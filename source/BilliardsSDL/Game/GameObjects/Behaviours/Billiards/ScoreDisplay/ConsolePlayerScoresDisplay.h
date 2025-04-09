#pragma once
#include <iostream>
#include <vector>

#include "IPlayerScoresDisplay.h"
#include "../Player/BilliardsPlayer.h"



class ConsolePlayerScoresDisplay : public IPlayerScoresDisplay
{
public:
	ConsolePlayerScoresDisplay();

	virtual void Init(const std::vector<BilliardsPlayer*>& players) override;
	virtual void UpdateDisplayedScore() override;

private:
	void ClearConsole() const;
	void PrintHeader() const;
	void PrintPlayer(BilliardsPlayer* player) const;


private:
	std::vector<BilliardsPlayer*> m_players;
};