#pragma once
#include "BilliardsGameSceneState.h"
#include "../../PauseMenu/PauseMenu.h"


class BilliardsGameSceneState_Paused : public BilliardsGameSceneState
{
public:
	BilliardsGameSceneState_Paused(PauseMenu* pauseMenu);

	virtual bool Update() override;
	virtual void Exit() override;
protected:
	virtual void DoEnter() override;


private:
	void SetupEnterPlaying();
	void SetupEnterOptions();
	void SetupRestartGame();
	void SetupQuitGame();


private:
	PauseMenu* m_pauseMenu;

	bool m_enterPlaying;
	bool m_enterOptions;
	bool m_restartGame;
	bool m_quitGame;
};