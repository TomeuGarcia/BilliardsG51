#include "BilliardsApplication.h"

BilliardsApplication::BilliardsApplication()
	: m_running(true), m_specifications(), 
	m_inputSystem(), 
	m_timeSystem(m_specifications.p_maxDeltaTime), 
	m_renderSystem(), 
	m_rngSystem(),
	m_gameEngine()
{
}

BilliardsApplication::~BilliardsApplication()
{
}

void BilliardsApplication::Run()
{
	InitSDL();
	InitSystems();
	InitGameEngine();

	GameLoop();

	CleanupGameEngine();
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
	m_renderSystem.Init(m_specifications.p_windowSize);	
	m_inputSystem.Init(m_renderSystem.GetWindow());
	m_timeSystem.Init();
	m_rngSystem.Init();
}

void BilliardsApplication::InitGameEngine()
{
	m_gameEngine.Init(m_specifications.p_gameSpecifications, &m_inputSystem, &m_renderSystem,
				&m_timeSystem, &m_rngSystem);
}



void BilliardsApplication::CleanupGameEngine()
{
	m_gameEngine.Cleanup();
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

		m_inputSystem.Update();
		m_timeSystem.Update();
		m_gameEngine.Update();

		m_gameEngine.Render();
		m_renderSystem.DrawRenderer();

		UpdateRunningFlag();
	}
}

void BilliardsApplication::UpdateRunningFlag()
{
	m_running = !m_inputSystem.GetWindowInputs().p_closeWindow || 
		m_gameEngine.p_quitApplication;
}
