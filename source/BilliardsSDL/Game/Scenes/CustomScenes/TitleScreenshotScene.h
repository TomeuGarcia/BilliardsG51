#pragma once
#include "../Scene.h"
#include "../../Systems/GameInput.h"
#include "../SceneManager.h"

#include "../../GameObjects/Behaviours/TitleScreenshot/TitleScreenshotManager.h"

#include "../../Audio/GameAudioManager.h"



class TitleScreenshotScene : public Scene
{
protected:
	virtual void CreateGameObjects() override;
	virtual void DoStart() override;
	virtual void DoUpdate() override;
};
