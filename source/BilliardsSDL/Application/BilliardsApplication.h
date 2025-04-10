#pragma once
#include <SDL.h>

#include "Systems/Render/RenderSystem.h"
#include "Systems/Audio/AudioSystem.h"
#include "Systems/Time/TimeSystem.h"
#include "Systems/Input/InputSystem.h"
#include "Systems/Random/RNGSystem.h"

#include "../Game/BilliardsGameEngine.h"


class BilliardsApplication
{
public:
	BilliardsApplication();
	~BilliardsApplication();
	void Run();

private:
	void InitSDL();
	void InitSystems();
	void InitGameEngine();

	void CleanupGameEngine();
	void CleanupSystems();
	void CleanupSDL();

private:
	void GameLoop();
	void UpdateRunningFlag();


private:
	bool m_running;	
	ApplicationSpecifications m_specifications;

	InputSystem m_inputSystem;
	TimeSystem m_timeSystem;
	RenderSystem m_renderSystem;
	AudioSystem m_audioSystem;
	RNGSystem m_rngSystem;

	BilliardsGameEngine m_gameEngine;
};

