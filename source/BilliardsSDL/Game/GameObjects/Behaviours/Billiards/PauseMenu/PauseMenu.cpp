#include "PauseMenu.h"

PauseMenu::PauseMenu(const GameObjectGroup& menuGameObjects, 
	MenuButton* backButton, MenuButton* optionsButton, MenuButton* restartButton, MenuButton* quitButton)
	: m_menuGameObjects(menuGameObjects),
	m_backButton(backButton), m_optionsButton(optionsButton), m_restartButton(restartButton), m_quitButton(quitButton)
{
}

void PauseMenu::Start()
{
	m_backButton->SetSelectedCallback(std::bind(&PauseMenu::Hide, this));
	m_optionsButton->SetSelectedCallback(std::bind(&PauseMenu::OnOptionsSelected, this));
	m_restartButton->SetSelectedCallback(std::bind(&PauseMenu::OnRestartSelected, this));
	m_quitButton->SetSelectedCallback(std::bind(&PauseMenu::OnQuitSelected, this));

	SilentHide();
}



void PauseMenu::SetOnBackCallback(const std::function<void()>& onBackCallback)
{
	m_onBackCallback = onBackCallback;
}

void PauseMenu::SetOnOptionsCallback(const std::function<void()>& onOptionsCallback)
{
	m_onOptionsCallback = onOptionsCallback;
}

void PauseMenu::SetOnRestartCallback(const std::function<void()>& onRestartCallback)
{
	m_onRestartCallback = onRestartCallback;
}

void PauseMenu::SetOnQuitCallback(const std::function<void()>& onQuitCallback)
{
	m_onQuitCallback = onQuitCallback;
}



void PauseMenu::Show()
{
	m_menuGameObjects.SetActive(true);
}

void PauseMenu::Hide()
{
	SilentHide();
	m_onBackCallback();
}

void PauseMenu::SilentHide()
{
	m_menuGameObjects.SetActive(false);
}



void PauseMenu::OnOptionsSelected()
{
	SilentHide();
	m_onOptionsCallback();
}

void PauseMenu::OnRestartSelected()
{
	SilentHide();
	m_onRestartCallback();
}

void PauseMenu::OnQuitSelected()
{
	SilentHide();
	m_onQuitCallback();
}
