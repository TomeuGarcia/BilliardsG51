#include "BilliardsApplication.h"

BilliardsApplication::BilliardsApplication()
	: _running(true), _specifications(640, 480), 
	_inputSystem(), _timeSystem(), _renderSystem(),
	_game()
{
}

BilliardsApplication::~BilliardsApplication()
{
}

void BilliardsApplication::Run()
{
	InitSDL();
	InitSystems();

	GameLoop();

	CleanupSystems();
	CleanupSDL();
}

void BilliardsApplication::InitSDL()
{
	int initResult = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	bool initialized = initResult >= 0;

	if (!initialized)
	{
		std::cout << SDL_GetError() << std::endl;
	}
}

void BilliardsApplication::InitSystems()
{
	_inputSystem.Init();
	_timeSystem.Init();
	_renderSystem.Init(_specifications);	
}



void BilliardsApplication::CleanupSystems()
{
	_renderSystem.Cleanup();
}

void BilliardsApplication::CleanupSDL()
{
	SDL_Quit();
}


void BilliardsApplication::GameLoop()
{
	_running = true;
	while (_running)
	{
		_timeSystem.Update();
		_inputSystem.Update();
		_game.Update();

		_renderSystem.ClearRenderer();
		_game.Render();
		_renderSystem.DrawRenderer();

		UpdateRunningFlag();
	}
}

void BilliardsApplication::UpdateRunningFlag()
{
	_running = !_inputSystem.GetWindowInputs().closeWindow;
}
