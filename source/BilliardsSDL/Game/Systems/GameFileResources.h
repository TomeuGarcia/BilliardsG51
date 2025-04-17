#pragma once
#include <filesystem>
#include "../../Application/Systems/Files/FilePathData.h"


class GameFileResources
{
public:
	GameFileResources(const std::filesystem::path& pathToResourceFiles);
	~GameFileResources();

public:
	static GameFileResources* GetInstance();

public:
	const FilePathData& GetOptionsFilePathData();
	const FilePathData& GetRankingFilePathData();


private:
	FilePathData m_optionsFilePathData;
	FilePathData m_rankingFilePathData;

private:
	static GameFileResources* s_instance;
};