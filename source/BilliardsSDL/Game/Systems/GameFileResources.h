#pragma once
#include "../../Application/Systems/Files/FilePathData.h"


class GameFileResources
{
public:
	GameFileResources(const std::string& pathToResourceFiles);
	~GameFileResources();

public:
	static GameFileResources* GetInstance();

public:
	const FilePathData& GetRankingFilePathData();


private:
	FilePathData m_rankingFilePathData;

private:
	static GameFileResources* s_instance;
};