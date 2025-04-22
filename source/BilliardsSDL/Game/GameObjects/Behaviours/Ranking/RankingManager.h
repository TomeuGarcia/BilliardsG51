#pragma once
#include "RankingFileData.h"
#include "../../../../Application/Systems/Files/Binary/BinaryFile.h"

#include "../../../Systems/GameFileResources.h"


class RankingManager
{
public:
	RankingManager();

	void Load();
	void Save();

	void ClearEntries();

	const std::vector<RankingEntry>& GetFilledRankingEntries();
	const std::vector<RankingEntry> GetRemainingEmptyRankingEntries();

	bool TryAddRankingEntry(const RankingEntry& rankingEntry);

private:
	bool TryReplaceBestPlayHighscore(std::vector<RankingEntry>& entries, const RankingEntry& rankingEntry);
	bool TryAddAsTopHighscore(std::vector<RankingEntry>& entries, const RankingEntry& rankingEntry);


private:
	BinaryFile m_rankingFile;
	RankingFileData m_rankingFileData;
	int m_maxEntries;
};