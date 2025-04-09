#pragma once
#include "../Scene.h"
#include "../../Systems/GameInput.h"
#include "../SceneManager.h"

#include "../../GameObjects/Behaviours/MainMenu/MainMenuManager.h"


class MainMenuScene : public Scene
{
protected:
	virtual void CreateGameObjects() override;
	virtual void DoStart() override;
	virtual void DoUpdate() override;
};