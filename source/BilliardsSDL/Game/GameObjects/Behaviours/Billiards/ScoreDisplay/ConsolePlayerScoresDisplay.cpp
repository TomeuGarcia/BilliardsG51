#include "ConsolePlayerScoresDisplay.h"

ConsolePlayerScoresDisplay::ConsolePlayerScoresDisplay()
	: m_players()
{
	m_players.reserve(2);
}


void ConsolePlayerScoresDisplay::Init(const std::vector<BilliardsPlayer*>& players)
{	
	for (size_t i = 0; i < players.size(); ++i)
	{
		m_players.emplace_back(players[i]);
	}
}

void ConsolePlayerScoresDisplay::UpdateDisplayedScore()
{
	ClearConsole();
	PrintHeader();

	for (size_t i = 0; i < m_players.size(); ++i)
	{
		PrintPlayer(m_players[i]);
	}
}


void ConsolePlayerScoresDisplay::ClearConsole() const
{
	system("cls");
}

void ConsolePlayerScoresDisplay::PrintHeader() const
{
	std::printf("SCORES\n");
}

void ConsolePlayerScoresDisplay::PrintPlayer(BilliardsPlayer* player) const
{
	std::printf("%s \t %i\n", player->GetName().c_str(), player->GetScore().GetCurrentValue());
}