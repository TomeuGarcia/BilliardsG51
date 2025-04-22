#include "RankingEntry.h"

RankingEntry::RankingEntry()
	: m_playerName("..."), m_playerHighscore(0)
{
}

RankingEntry::RankingEntry(const std::string& playerName, const int& playerHighscore)
	: m_playerName(playerName), m_playerHighscore(playerHighscore)
{
}

std::string_view RankingEntry::GetPlayerName() const
{
	return m_playerName;
}

int RankingEntry::GetPlayerHighscore() const
{
	return m_playerHighscore;
}

void RankingEntry::OverwritePlayerHighscore(const int& newPlayerHighscore)
{
	m_playerHighscore = newPlayerHighscore;
}



void RankingEntry::ReadAsBinary(std::ifstream& inputStream)
{
	BinaryUtilities::ReadString(inputStream, m_playerName);
	BinaryUtilities::ReadInt(inputStream, m_playerHighscore);
}


void RankingEntry::WriteAsBinary(std::ofstream& outputStream)
{
	BinaryUtilities::WriteString(outputStream, m_playerName);
	BinaryUtilities::WriteInt(outputStream, m_playerHighscore);
}
