#include "BilliardsGameEngine.h"


BilliardsGameEngine::BilliardsGameEngine()
	: m_gameAppInteractions(), m_gameTime(nullptr), m_gameInput(nullptr),
	m_gameRenderManager(nullptr), 
	m_gameAudioManager(nullptr), m_gameMusicService(nullptr),
	m_physicsManager(nullptr),
	m_sceneManager(nullptr), m_uiCaster(nullptr),
	m_gameAssetResources(nullptr),	m_gameFileResources(nullptr),
	m_gameSpacesComputer(nullptr),  
	m_gameRandom(nullptr), m_gameTweener(nullptr), m_delayedCallScheduler(nullptr)
{
}

BilliardsGameEngine::~BilliardsGameEngine()
{
	delete m_delayedCallScheduler;
	delete m_gameTweener;
	delete m_gameRandom;
	delete m_gameSpacesComputer;
	delete m_sceneManager;
	delete m_physicsManager;
	delete m_gameMusicService;
	delete m_gameAudioManager;
	delete m_gameRenderManager;
	delete m_gameFileResources;
	delete m_gameAssetResources;
	delete m_uiCaster;
	delete m_gameInput;
	delete m_gameTime;
	delete m_gameAppInteractions;
}

void BilliardsGameEngine::Init(const GameSpecifications& specifications, 
		IInputState* inputState, RenderSystem* renderSystem, AudioSystem* audioSystem,
		ITimeState* timeState, RNGSystem* rngSystem)
{
	m_gameAppInteractions = new GameAppInteractions();
	m_gameTime = new GameTime(timeState);
	m_gameInput = new GameInput(inputState);
	m_uiCaster = new UICaster(m_gameInput);
	
	m_gameAssetResources = new GameAssetResources(specifications.p_worldWidthInWindow / renderSystem->GetWindowSize().x,
												  specifications.p_pathToResourceImages,
												  specifications.p_pathToResourceFonts,
												  specifications.p_pathToResourceAudios);
	m_gameFileResources = new GameFileResources(specifications.p_pathToResourceFiles);

	m_gameRenderManager = new GameRenderManager(renderSystem);
	m_gameAudioManager = new GameAudioManager(audioSystem);
	m_gameMusicService = new GameMusicService();
	m_physicsManager = new Physics2DManager();
	m_sceneManager = new SceneManager();

	m_gameSpacesComputer = new GameSpacesComputer(renderSystem, specifications.p_worldWidthInWindow);
	m_gameRandom = new GameRandom(rngSystem);
	m_gameTweener = new GameTweener();
	m_delayedCallScheduler = new GameDelayedCallScheduler();

	m_gameSpacesComputer->Update();
	m_sceneManager->Init(specifications.p_startingScene);
}

void BilliardsGameEngine::Cleanup()
{
	m_sceneManager->Cleanup();
}


void BilliardsGameEngine::Update()
{
	const float deltaTime = m_gameTime->GetDeltaTime();

	m_gameSpacesComputer->Update();
	m_sceneManager->UpdateLoading();
	m_sceneManager->GetActiveScene()->Update();
	m_gameRenderManager->UpdateRendererQueue();
	m_uiCaster->Update(deltaTime);

	m_gameTweener->Update(deltaTime);
	m_delayedCallScheduler->Update(deltaTime);
	m_physicsManager->Update(deltaTime);
}

void BilliardsGameEngine::Render()
{
	m_gameRenderManager->DrawRendererQueue();
}


bool BilliardsGameEngine::WantsToQuit() const
{
	return m_gameAppInteractions->WantsToQuit();
}
