#include "BilliardsApplication.h"

BilliardsApplication::BilliardsApplication()
	: m_running(true), m_specifications(Vector2<int>(960, 540)), 
	m_inputSystem(), m_timeSystem(), m_renderSystem(),
	m_game()
{
}

BilliardsApplication::~BilliardsApplication()
{
}

void BilliardsApplication::Run()
{
	InitSDL();
	InitSystems();
	InitGame();

	GameLoop();

	CleanupGame();
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
	m_inputSystem.Init();
	m_timeSystem.Init();
	m_renderSystem.Init(m_specifications.p_windowSize);	
}

void BilliardsApplication::InitGame()
{
	GameSystems gameSystems{ &m_inputSystem, &m_renderSystem, &m_timeSystem };
	m_game.Init(gameSystems);
}



void BilliardsApplication::CleanupGame()
{
	m_game.Cleanup();
}

void BilliardsApplication::CleanupSystems()
{
	m_renderSystem.Cleanup();
}

void BilliardsApplication::CleanupSDL()
{
	SDL_Quit();
}


void BilliardsApplication::GameLoop()
{
	m_running = true;
	while (m_running)
	{
		m_renderSystem.ClearRenderer();

		m_timeSystem.Update();
		m_inputSystem.Update();
		m_game.Update();

		m_game.Render();
		m_renderSystem.DrawRenderer();

		UpdateRunningFlag();
	}
}

void BilliardsApplication::UpdateRunningFlag()
{
	m_running = !m_inputSystem.GetWindowInputs().p_closeWindow || 
				 m_game.p_quitApplication;
}
