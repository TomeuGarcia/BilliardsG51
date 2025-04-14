#pragma once
#include "../../Behaviour.h"
#include "States/BilliardsGameSceneState_Playing.h"
#include "States/BilliardsGameSceneState_Paused.h"
#include "States/BilliardsGameSceneState_Options.h"

#include "../../../../Scenes/SceneManager.h"



class BilliardsGameSceneManager : public Behaviour
{
public:
	BilliardsGameSceneManager(BilliardsGameplayStateBlackboard* gameplayBlackboard, PauseMenu* pauseMenu, OptionsMenu* optionsMenu);

	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDestroy() override;

private:
	void RestartGame();
	void QuitToMainMenu();


private:
	std::unordered_map<BilliardsGameSceneState::Type, std::shared_ptr<BilliardsGameSceneState>> m_statesMap;
	BilliardsGameSceneState* m_currentState;
};