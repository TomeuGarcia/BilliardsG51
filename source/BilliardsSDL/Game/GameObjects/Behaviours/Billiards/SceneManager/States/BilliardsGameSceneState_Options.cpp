#include "BilliardsGameSceneState_Options.h"

BilliardsGameSceneState_Options::BilliardsGameSceneState_Options(OptionsMenu* optionsMenu)
	: m_optionsMenu(optionsMenu), m_enterPaused(false)
{
	m_optionsMenu->SetOnHideCallback(std::bind(&BilliardsGameSceneState_Options::SetupEnterPaused, this));
}


void BilliardsGameSceneState_Options::DoEnter()
{
	m_enterPaused = false;
	m_optionsMenu->Show();
}

bool BilliardsGameSceneState_Options::Update()
{
	if (GameInput::GetInstance()->GetKeyDown(KeyCode::Esc))
	{
		SetupEnterPaused();
		m_optionsMenu->SilentHide();
	}

	if (m_enterPaused)
	{
		SetNextState(BilliardsGameSceneState::Type::Paused);
		return true;
	}

	return false;
}

void BilliardsGameSceneState_Options::Exit()
{
}



void BilliardsGameSceneState_Options::SetupEnterPaused()
{
	m_enterPaused = true;
}
