#pragma once
#include <utility>
#include <iostream>

#include "Systems/GameAppInteractions.h"
#include "Systems/GameTime.h"
#include "Systems/GameInput.h"
#include "Systems/GameAssetResources.h"
#include "Systems/GameSpacesComputer.h"
#include "Systems/GameRandom.h"
#include "Systems/GameTweener.h"
#include "Physics/Physics2DManager.h"
#include "Render/GameRenderManager.h"
#include "Scenes/SceneManager.h"
#include "UI/UICaster.h"


class BilliardsGameEngine
{
public:
	BilliardsGameEngine();
	~BilliardsGameEngine();
	void Init(const GameSpecifications& specifications,
			  IInputState* inputState, RenderSystem* renderSystem, ITimeState* timeState, RNGSystem* rngSystem);
	void Cleanup();

	void Update();
	void Render();

	bool WantsToQuit() const;


private:
	GameAppInteractions* m_gameAppInteractions;
	GameTime* m_gameTime;
	GameInput* m_gameInput;
	GameRenderManager* m_gameRenderManager;
	Physics2DManager* m_physicsManager;
	SceneManager* m_sceneManager;
	UICaster* m_uiCaster;
	GameAssetResources* m_gameAssetResources;
	GameSpacesComputer* m_gameSpacesComputer;
	GameRandom* m_gameRandom;
	GameTweener* m_gameTweener;
};