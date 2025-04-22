#include "RankingFileData.h"

RankingFileData::RankingFileData()
	: m_entries()
{
}

std::vector<RankingEntry>& RankingFileData::GetEntries()
{
	return m_entries;
}

void RankingFileData::ReadAsBinary(std::ifstream& inputStream)
{
	int entriesSize;
	BinaryUtilities::ReadInt(inputStream, entriesSize);
	m_entries.resize(entriesSize);

	for (int i = 0; i < entriesSize; ++i)
	{
		m_entries[i].ReadAsBinary(inputStream);
	}
}


void RankingFileData::WriteAsBinary(std::ofstream& outputStream)
{
	int entriesSize = m_entries.size();
	BinaryUtilities::WriteInt(outputStream, entriesSize);

	for (int i = 0; i < entriesSize; ++i)
	{
		m_entries[i].WriteAsBinary(outputStream);
	}
}
