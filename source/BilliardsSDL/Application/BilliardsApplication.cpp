#include "BilliardsApplication.h"

BilliardsApplication::BilliardsApplication()
	: _specifications(640, 480), _renderSystem()
{
	printf("App created\n");
}

BilliardsApplication::~BilliardsApplication()
{
	printf("App destroyed\n");
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
}
