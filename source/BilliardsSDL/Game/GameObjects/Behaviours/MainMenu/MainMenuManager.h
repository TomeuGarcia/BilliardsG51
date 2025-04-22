#pragma once

#include "../Behaviour.h"
#include "../GameOptions/OptionsMenu.h"
#include "../../GameObjectGroup.h"
#include "MainMenuBilliardsBoardManager.h"

#include "../../../Scenes/SceneManager.h"



class MainMenuManager : public Behaviour
{
public:
	MainMenuManager(const std::shared_ptr<MainMenuBilliardsBoardManager>& boardManager,
		MenuButton* playButton, MenuButton* rankingButton, MenuButton* optionsButton, MenuButton* quitButton,
		OptionsMenu* optionsMenu, const GameObjectGroup& objectsToHideWhenOptionsShown);

	virtual void Start() override;


private:
	void OnOptionsButtonSelected();
	void OnOptionsMenuHidden();



private:
	std::shared_ptr<MainMenuBilliardsBoardManager> m_boardManager;

	MenuButton* m_playButton;
	MenuButton* m_rankingButton;
	MenuButton* m_optionsButton;
	MenuButton* m_quitButton;

	OptionsMenu* m_optionsMenu;
	GameObjectGroup m_objectsToHideWhenOptionsShown;
};