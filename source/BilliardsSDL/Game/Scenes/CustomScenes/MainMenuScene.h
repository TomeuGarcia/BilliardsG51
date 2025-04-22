#pragma once
#include "../Scene.h"
#include "../../Systems/GameInput.h"
#include "../SceneManager.h"

#include "../../GameObjects/Behaviours/MainMenu/MainMenuManager.h"

#include "../../Audio/GameAudioManager.h"

#include "../../GameObjects/Behaviours/CustomUI/MenuIncDecButton.h"




class MainMenuScene : public Scene
{
protected:
	virtual void CreateGameObjects() override;
	virtual void DoStart() override;
	virtual void DoUpdate() override;
};