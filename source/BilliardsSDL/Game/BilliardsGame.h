#pragma once
#include <utility>
#include <iostream>

#include "Systems/GameTime.h"
#include "Systems/GameInput.h"
#include "Systems/GameAssetResources.h"
#include "Render/GameRenderManager.h"
#include "Scenes/SceneManager.h"


class BilliardsGame
{
public:
	BilliardsGame();
	~BilliardsGame();
	void Init(const GameSpecifications& specifications,
			  IInputState* inputState, RenderSystem* renderSystem, ITimeState* timeState);
	void Cleanup();

	void Update();
	void Render();


public:
	bool p_quitApplication;
private:
	GameTime* m_gameTime;
	GameInput* m_gameInput;
	GameRenderManager* m_gameRenderManager;
	SceneManager* m_sceneManager;
	GameAssetResources* m_gameAssetResources;
};