#include "MainMenuManager.h"



MainMenuManager::MainMenuManager(const std::shared_ptr<MainMenuBilliardsBoardManager>& boardManager, 
	MenuButton* playButton, MenuButton* rankingButton, MenuButton* optionsButton, MenuButton* quitButton, 
	OptionsMenu* optionsMenu, const GameObjectGroup& objectsToHideWhenOptionsShown)
	:
	m_boardManager(boardManager),
	m_playButton(playButton), m_rankingButton(rankingButton), m_optionsButton(optionsButton), m_quitButton(quitButton),
	m_optionsMenu(optionsMenu), m_objectsToHideWhenOptionsShown(objectsToHideWhenOptionsShown)
{
}


void MainMenuManager::Start()
{
	m_playButton->SetSelectedCallback(		[]() { SceneManager::GetInstance()->LoadScene(SceneName::BilliardGame); });
	m_rankingButton->SetSelectedCallback(	[]() { SceneManager::GetInstance()->LoadScene(SceneName::Ranking); });
	m_optionsButton->SetSelectedCallback(	std::bind(&MainMenuManager::OnOptionsButtonSelected, this));
	m_quitButton->SetSelectedCallback(		[]() { GameAppInteractions::GetInstance()->Quit(); });	

	m_optionsMenu->SetOnHideCallback(		std::bind(&MainMenuManager::OnOptionsMenuHidden, this));
}


void MainMenuManager::OnOptionsButtonSelected()
{
	m_objectsToHideWhenOptionsShown.SetActive(false);
	m_optionsMenu->Show();
}

void MainMenuManager::OnOptionsMenuHidden()
{
	m_objectsToHideWhenOptionsShown.SetActive(true);
}
