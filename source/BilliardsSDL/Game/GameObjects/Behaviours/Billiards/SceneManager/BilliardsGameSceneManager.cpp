#include "BilliardsGameSceneManager.h"

BilliardsGameSceneManager::BilliardsGameSceneManager(BilliardsGameplayStateBlackboard* gameplayBlackboard, PauseMenu* pauseMenu, OptionsMenu* optionsMenu)
	: m_statesMap(), m_currentState(nullptr)
{
	m_statesMap[BilliardsGameSceneState::Type::Playing] = std::make_shared<BilliardsGameSceneState_Playing>(gameplayBlackboard);
	m_statesMap[BilliardsGameSceneState::Type::Paused] =  std::make_shared<BilliardsGameSceneState_Paused>(pauseMenu);
	m_statesMap[BilliardsGameSceneState::Type::Options] = std::make_shared<BilliardsGameSceneState_Options>(optionsMenu);

}

void BilliardsGameSceneManager::Start()
{
	m_currentState = m_statesMap[BilliardsGameSceneState::Type::Playing].get();
	m_currentState->Enter();
}

void BilliardsGameSceneManager::Update()
{
	if (m_currentState->Update())
	{
		m_currentState->Exit();
		const BilliardsGameSceneState::Type nextState = m_currentState->GetNextState();

		if (nextState == BilliardsGameSceneState::Type::Restart)
		{
			RestartGame();
			return;
		}
		else if (nextState == BilliardsGameSceneState::Type::Quit)
		{
			QuitToMainMenu();
			return;
		}

		m_currentState = m_statesMap[nextState].get();
		m_currentState->Enter();
	}
}

void BilliardsGameSceneManager::OnDestroy()
{
	m_currentState->Exit();
	m_currentState = nullptr;
}



void BilliardsGameSceneManager::RestartGame()
{
	SceneManager::GetInstance()->LoadScene(SceneName::BilliardGame);
}

void BilliardsGameSceneManager::QuitToMainMenu()
{
	SceneManager::GetInstance()->LoadScene(SceneName::MainMenu);
}
