#include "BilliardsGameEngine.h"


BilliardsGameEngine::BilliardsGameEngine()
	: p_quitApplication(false), m_gameTime(nullptr), m_gameInput(nullptr), 
	m_gameRenderManager(nullptr), m_physicsManager(nullptr),
	m_sceneManager(nullptr), m_gameAssetResources(nullptr),	m_gameSpacesComputer(nullptr),  
	m_gameRandom(nullptr), m_gameTweener(nullptr)
{
}

BilliardsGameEngine::~BilliardsGameEngine()
{
	delete m_gameTweener;
	delete m_gameRandom;
	delete m_gameSpacesComputer;
	delete m_gameAssetResources;
	delete m_sceneManager;
	delete m_physicsManager;
	delete m_gameRenderManager;
	delete m_gameInput;
	delete m_gameTime;
}

void BilliardsGameEngine::Init(const GameSpecifications& specifications, 
		IInputState* inputState, RenderSystem* renderSystem, ITimeState* timeState, RNGSystem* rngSystem)
{
	
	m_gameTime = new GameTime(timeState);
	m_gameInput = new GameInput(inputState);
	m_gameRenderManager = new GameRenderManager(renderSystem);
	m_physicsManager = new Physics2DManager();
	m_sceneManager = new SceneManager();
	m_gameAssetResources = new GameAssetResources(specifications.p_worldWidthInWindow / renderSystem->GetWindowSize().x,
												  specifications.p_pathToResourceImages,
												  specifications.p_pathToResourceFonts,
												  specifications.p_pathToResourceAudios);
	m_gameSpacesComputer = new GameSpacesComputer(renderSystem, specifications.p_worldWidthInWindow);
	m_gameRandom = new GameRandom(rngSystem);
	m_gameTweener = new GameTweener();

	m_gameSpacesComputer->Update();
	m_sceneManager->Init(specifications.p_startingScene);
}

void BilliardsGameEngine::Cleanup()
{
	m_sceneManager->Cleanup();
}


void BilliardsGameEngine::Update()
{
	m_gameSpacesComputer->Update();
	m_sceneManager->UpdateLoading();
	m_sceneManager->GetActiveScene()->Update();

	m_gameTweener->Update(m_gameTime->GetDeltaTime());
	m_physicsManager->Update(m_gameTime->GetDeltaTime());
}

void BilliardsGameEngine::Render()
{
	m_sceneManager->GetActiveScene()->Render();
}