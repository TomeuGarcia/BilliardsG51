#pragma once
#include <vector>
#include "RankingEntry.h"



class RankingFileData : public IBinarySerializable
{
public:
	RankingFileData();

	std::vector<RankingEntry>& GetEntries();

public:
	virtual void ReadAsBinary(std::ifstream& inputStream) override;
	virtual void WriteAsBinary(std::ofstream& outputStream) override;


private:
	std::vector<RankingEntry> m_entries;
};