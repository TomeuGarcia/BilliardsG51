#pragma once
#include <functional>

#include "../Behaviour.h"
#include "../../GameObjectGroup.h"
#include "../CustomUI/MenuIncDecButton.h"
#include "../CustomUI/MenuButton.h"
#include "GameOptionsManager.h"



class OptionsMenu : public Behaviour
{
public:
	OptionsMenu(const GameObjectGroup& menuGameObjects, 
		MenuButton* backButton,
		MenuIncDecButton* masterVolumeIncDecButton,	MenuIncDecButton* musicVolumeIncDecButton, MenuIncDecButton* sfxVolumeIncDecButton);

	virtual void Start() override;
	virtual void OnDestroy() override;


public:
	void SetOnHideCallback(const std::function<void()>& onHideCallback);

	bool IsBeingShown();
	void Show();
	void SilentHide();

private:
	void Hide();



private:
	GameOptionsManager m_gameOptionsManager;

	GameObjectGroup m_menuGameObjects;
	MenuButton* m_backButton;
	MenuIncDecButton* m_masterVolumeIncDecButton;
	MenuIncDecButton* m_musicVolumeIncDecButton;
	MenuIncDecButton* m_sfxVolumeIncDecButton;

	std::function<void()> m_onHideCallback;
};