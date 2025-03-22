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

	void CleanupSystems();
	void CleanupSDL();

private:
	void GameLoop();
	void UpdateRunningFlag();


private:
	bool _running;
	
	ApplicationSpecifications _specifications;
	InputSystem _inputSystem;
	TimeSystem _timeSystem;
	RenderSystem _renderSystem;

	BilliardsGame _game;
};

