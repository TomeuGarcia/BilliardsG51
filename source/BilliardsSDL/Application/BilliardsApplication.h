#pragma once
#include <SDL.h>
//#include <SDL_mixer.h>
//#include <SDL_ttf.h>

#include "Systems/Render/RenderSystem.h"
#include "Systems/Time/TimeSystem.h"
#include "Systems/Input/InputSystem.h"

#include "../Game/BilliardsGame.h"


class BilliardsApplication
{
public:
	BilliardsApplication();
	~BilliardsApplication();
	void Run();

private:
	void InitSDL();
	void InitSystems();
	void InitGame();

	void CleanupGame();
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

	BilliardsGame m_game;
};

