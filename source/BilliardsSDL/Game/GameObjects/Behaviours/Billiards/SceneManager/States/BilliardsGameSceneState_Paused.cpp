#include "BilliardsGameSceneState_Paused.h"

BilliardsGameSceneState_Paused::BilliardsGameSceneState_Paused(PauseMenu* pauseMenu)
	: m_pauseMenu(pauseMenu),
	m_enterPlaying(false), m_enterOptions(false), m_restartGame(false), m_quitGame(false)
{
	m_pauseMenu->SetOnBackCallback(		std::bind(&BilliardsGameSceneState_Paused::SetupEnterPlaying, this));
	m_pauseMenu->SetOnOptionsCallback(	std::bind(&BilliardsGameSceneState_Paused::SetupEnterOptions, this));
	m_pauseMenu->SetOnRestartCallback(	std::bind(&BilliardsGameSceneState_Paused::SetupRestartGame, this));
	m_pauseMenu->SetOnQuitCallback(		std::bind(&BilliardsGameSceneState_Paused::SetupQuitGame, this));
}


void BilliardsGameSceneState_Paused::DoEnter()
{
	m_enterPlaying = false;
	m_enterOptions = false;
	m_restartGame = false;
	m_quitGame = false;

	m_pauseMenu->Show();
}

bool BilliardsGameSceneState_Paused::Update()
{
	if (GameInput::GetInstance()->GetKeyDown(KeyCode::Esc))
	{
		m_pauseMenu->SilentHide();
		SetupEnterPlaying();
	}

	if (m_enterPlaying)
	{
		SetNextState(BilliardsGameSceneState::Type::Playing);
		return true;
	}
	
	if (m_enterOptions)
	{
		SetNextState(BilliardsGameSceneState::Type::Options);
		return true;
	}

	if (m_restartGame)
	{
		SetNextState(BilliardsGameSceneState::Type::Restart);
		return true;
	}

	if (m_quitGame)
	{
		SetNextState(BilliardsGameSceneState::Type::Quit);
		return true;
	}

	return false;
}

void BilliardsGameSceneState_Paused::Exit()
{
}



void BilliardsGameSceneState_Paused::SetupEnterPlaying()
{
	m_enterPlaying = true;
}

void BilliardsGameSceneState_Paused::SetupEnterOptions()
{
	m_enterOptions = true;
}

void BilliardsGameSceneState_Paused::SetupRestartGame()
{
	m_restartGame = true;
}

void BilliardsGameSceneState_Paused::SetupQuitGame()
{
	m_quitGame = true;
}
