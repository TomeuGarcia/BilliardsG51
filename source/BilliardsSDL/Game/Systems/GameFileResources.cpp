#include "GameFileResources.h"


GameFileResources* GameFileResources::s_instance = nullptr;

GameFileResources::GameFileResources(const std::string& pathToResourceFiles) :
	m_optionsFilePathData(pathToResourceFiles, "Options"),
	m_rankingFilePathData(pathToResourceFiles, "Ranking")
{
	s_instance = this;
}

GameFileResources::~GameFileResources()
{
	s_instance = nullptr;
}



GameFileResources* GameFileResources::GetInstance()
{
	return s_instance;
}



const FilePathData& GameFileResources::GetOptionsFilePathData()
{
	return m_optionsFilePathData;
}

const FilePathData& GameFileResources::GetRankingFilePathData()
{
	return m_rankingFilePathData;
}


