#include "OptionsMenu.h"

OptionsMenu::OptionsMenu(const GameObjectGroup& menuGameObjects,
	MenuButton* backButton,
	MenuIncDecButton* masterVolumeIncDecButton, MenuIncDecButton* musicVolumeIncDecButton, MenuIncDecButton* sfxVolumeIncDecButton)
	: 
	m_gameOptionsManager(),
	m_menuGameObjects(menuGameObjects),
	m_backButton(backButton),
	m_masterVolumeIncDecButton(masterVolumeIncDecButton), 
	m_musicVolumeIncDecButton(musicVolumeIncDecButton), 
	m_sfxVolumeIncDecButton(sfxVolumeIncDecButton)
{
	m_gameOptionsManager.Load();
}


void OptionsMenu::Start()
{	
	m_backButton->SetSelectedCallback(std::bind(&OptionsMenu::Hide, this));

	m_masterVolumeIncDecButton->SetValueUpdateCallback(
		[](int masterVolume100) { GameAudioManager::GetInstance()->SetMasterVolume(masterVolume100 / 100.0f); }
	);
	m_musicVolumeIncDecButton->SetValueUpdateCallback(
		[](int musicVolume100) { GameAudioManager::GetInstance()->SetMusicVolume(musicVolume100 / 100.0f); }
	);
	m_sfxVolumeIncDecButton->SetValueUpdateCallback(
		[](int sfxVolume100) { GameAudioManager::GetInstance()->SetSFXVolume(sfxVolume100 / 100.0f); }
	);

	SilentHide();
}


void OptionsMenu::OnDestroy()
{
	m_gameOptionsManager.Save();
}



void OptionsMenu::SetOnHideCallback(const std::function<void()>& onHideCallback)
{
	m_onHideCallback = onHideCallback;
}



bool OptionsMenu::IsBeingShown()
{
	return m_backButton->GetGameObject()->IsActive();
}

void OptionsMenu::Show()
{
	m_menuGameObjects.SetActive(true);
}

void OptionsMenu::Hide()
{
	SilentHide();
	m_onHideCallback();
}

void OptionsMenu::SilentHide()
{
	m_menuGameObjects.SetActive(false);
}
