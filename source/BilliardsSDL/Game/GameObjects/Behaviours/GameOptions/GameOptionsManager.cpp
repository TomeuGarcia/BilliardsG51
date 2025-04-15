#include "GameOptionsManager.h"

GameOptionsManager::GameOptionsManager()
	: m_optionsFile(GameFileResources::GetInstance()->GetOptionsFilePathData()),
	m_gameAudioFileData(100, 50, 50)
{
}



void GameOptionsManager::Load()
{
	m_optionsFile.Read(&m_gameAudioFileData);

	GameAudioManager::GetInstance()->SetMasterVolume(ToVolume01(m_gameAudioFileData.GetMasterVolume()));
	GameAudioManager::GetInstance()->SetMusicVolume( ToVolume01(m_gameAudioFileData.GetMusicVolume()));
	GameAudioManager::GetInstance()->SetSFXVolume(	 ToVolume01(m_gameAudioFileData.GetSFXVolume()));
}

void GameOptionsManager::Save()
{
	m_gameAudioFileData.SetMasterVolume(ToVolume100(GameAudioManager::GetInstance()->GetMasterVolume01()));
	m_gameAudioFileData.SetMusicVolume( ToVolume100(GameAudioManager::GetInstance()->GetMusicVolume01()));
	m_gameAudioFileData.SetSFXVolume(	ToVolume100(GameAudioManager::GetInstance()->GetSFXVolume01()));

	m_optionsFile.Write(&m_gameAudioFileData);
}


const GameAudioFileData& GameOptionsManager::GetGameAudioData()
{
	return m_gameAudioFileData;
}


const float GameOptionsManager::ToVolume01(const int& volume100)
{
	return volume100 / 100.0f;
}

const int GameOptionsManager::ToVolume100(const float& volume01)
{
	return volume01 * 100;
}

