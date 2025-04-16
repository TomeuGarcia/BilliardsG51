#include "GameOptionsManager.h"

GameOptionsManager::GameOptionsManager()
	: m_optionsFile(GameFileResources::GetInstance()->GetOptionsFilePathData()),
	m_gameOptionsFileData()
{
}



void GameOptionsManager::Load()
{
	m_optionsFile.Read(&m_gameOptionsFileData);

	GameAudioManager::GetInstance()->SetMasterVolume(To01(m_gameOptionsFileData.GetAudio().GetMasterVolume()));
	GameAudioManager::GetInstance()->SetMusicVolume( To01(m_gameOptionsFileData.GetAudio().GetMusicVolume()));
	GameAudioManager::GetInstance()->SetSFXVolume(	 To01(m_gameOptionsFileData.GetAudio().GetSFXVolume()));

	GameRenderManager::GetInstance()->GetCameraFunctionalities()->GetCameraShakeSettings()->SetShakeAmount(
		To01(m_gameOptionsFileData.GetRender().GetCameraShakeAmount())
	);
}

void GameOptionsManager::Save()
{
	m_gameOptionsFileData.GetAudio().SetMasterVolume(To100(GameAudioManager::GetInstance()->GetMasterVolume01()));
	m_gameOptionsFileData.GetAudio().SetMusicVolume( To100(GameAudioManager::GetInstance()->GetMusicVolume01()));
	m_gameOptionsFileData.GetAudio().SetSFXVolume(	To100(GameAudioManager::GetInstance()->GetSFXVolume01()));

	m_gameOptionsFileData.GetRender().SetCameraShakeAmount(
		To100(GameRenderManager::GetInstance()->GetCameraFunctionalities()->GetCameraShakeSettings()->GetShakeAmount())
	);	

	m_optionsFile.Write(&m_gameOptionsFileData);
}


const GameAudioFileData& GameOptionsManager::GetGameAudioData()
{
	return m_gameOptionsFileData.GetAudio();
}

const GameRenderFileData& GameOptionsManager::GetGameRenderData()
{
	return m_gameOptionsFileData.GetRender();
}


const float GameOptionsManager::To01(const int& value100)
{
	return value100 / 100.0f;
}

const int GameOptionsManager::To100(const float& value01)
{
	return value01 * 100;
}

