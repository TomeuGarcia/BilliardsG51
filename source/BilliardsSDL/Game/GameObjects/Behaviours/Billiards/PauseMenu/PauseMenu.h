#pragma once
#include "../../Behaviour.h"
#include "../../../GameObjectGroup.h"
#include "../../CustomUI/MenuButton.h"



class PauseMenu : public Behaviour
{
public:
	PauseMenu(const GameObjectGroup& menuGameObjects,
		MenuButton* backButton,	MenuButton* optionsButton, MenuButton* restartButton, MenuButton* quitButton);

	virtual void Start() override;

public:
	void SetOnBackCallback(const std::function<void()>& onBackCallback);
	void SetOnOptionsCallback(const std::function<void()>& onOptionsCallback);
	void SetOnRestartCallback(const std::function<void()>& onRestartCallback);
	void SetOnQuitCallback(const std::function<void()>& onQuitCallback);


	void Show();
	void SilentHide();

private:
	void Hide();

	void OnOptionsSelected();
	void OnRestartSelected();
	void OnQuitSelected();


private:
	GameObjectGroup m_menuGameObjects;
	MenuButton* m_backButton;
	MenuButton* m_optionsButton;
	MenuButton* m_restartButton;
	MenuButton* m_quitButton;

	std::function<void()> m_onBackCallback;
	std::function<void()> m_onOptionsCallback;
	std::function<void()> m_onRestartCallback;
	std::function<void()> m_onQuitCallback;
};