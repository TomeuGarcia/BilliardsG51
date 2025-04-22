#pragma once
#include "../../../../Application/Systems/Files/Binary/IBinarySerializable.h"


class RankingEntry : public IBinarySerializable
{
public:
	RankingEntry();
	RankingEntry(const std::string& playerName, const int& playerHighscore);

	std::string_view GetPlayerName() const;
	int GetPlayerHighscore() const;
	void OverwritePlayerHighscore(const int& newPlayerHighscore);


public:
	virtual void ReadAsBinary(std::ifstream& inputStream) override;
	virtual void WriteAsBinary(std::ofstream& outputStream) override;


private:
	std::string m_playerName;
	int m_playerHighscore;
};