#include "RankingManager.h"

RankingManager::RankingManager()
	: m_rankingFile(GameFileResources::GetInstance()->GetRankingFilePathData()),
	m_rankingFileData(),
	m_maxEntries(10)
{
}

void RankingManager::Load()
{
	m_rankingFile.Read(&m_rankingFileData);
}

void RankingManager::Save()
{
	m_rankingFile.Write(&m_rankingFileData);
}

void RankingManager::ClearEntries()
{
	m_rankingFileData.GetEntries().clear();
}



const std::vector<RankingEntry>& RankingManager::GetFilledRankingEntries()
{
	return m_rankingFileData.GetEntries();
}

const std::vector<RankingEntry> RankingManager::GetRemainingEmptyRankingEntries()
{
	return std::vector<RankingEntry>(m_maxEntries - m_rankingFileData.GetEntries().size());
}



bool RankingManager::TryAddRankingEntry(const RankingEntry& rankingEntry)
{
	std::vector<RankingEntry>& entries = m_rankingFileData.GetEntries();
	
	if (TryReplaceBestPlayHighscore(entries, rankingEntry))
	{
		return true;
	}

	if (TryAddAsTopHighscore(entries, rankingEntry))
	{
		return true;
	}

	return false;
}

bool RankingManager::TryReplaceBestPlayHighscore(std::vector<RankingEntry>& entries, const RankingEntry& rankingEntry)
{
	for (auto it = entries.begin(); it != entries.end(); ++it)
	{
		bool playerAlreadyInRanking = it->GetPlayerName().compare(rankingEntry.GetPlayerName()) == 0;
		if (playerAlreadyInRanking)
		{
			if (it->GetPlayerHighscore() < rankingEntry.GetPlayerHighscore())
			{
				it->OverwritePlayerHighscore(rankingEntry.GetPlayerHighscore());
				
				for (auto it2 = entries.begin(); it2 != it; ++it2)
				{
					if (it2->GetPlayerHighscore() < rankingEntry.GetPlayerHighscore())
					{
						entries.erase(it);
						entries.insert(it2, rankingEntry);
						break;
					}
				}
			}
			return true;
		}
	}

	return false;
}

bool RankingManager::TryAddAsTopHighscore(std::vector<RankingEntry>& entries, const RankingEntry& rankingEntry)
{
	for (auto it = entries.begin(); it != entries.end(); ++it)
	{
		if (it->GetPlayerHighscore() < rankingEntry.GetPlayerHighscore())
		{
			entries.insert(it, rankingEntry);

			if (entries.size() > m_maxEntries)
			{
				entries.erase(entries.end() - 1);
			}
			return true;
		}
	}

	if (entries.size() < m_maxEntries)
	{
		entries.emplace_back(rankingEntry);
	}

	return false;
}



