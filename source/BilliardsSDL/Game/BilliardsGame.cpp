#include "BilliardsGame.h"


BilliardsGame::BilliardsGame()
	: p_quitApplication(false), m_gameTime(nullptr), m_gameInput(nullptr), m_gameRenderManager(nullptr),
	m_gameSpacesComputer(nullptr)
{
}

BilliardsGame::~BilliardsGame()
{
	delete m_gameSpacesComputer;
	delete m_gameAssetResources;
	delete m_sceneManager;
	delete m_gameRenderManager;
	delete m_gameInput;
	delete m_gameTime;
}

void BilliardsGame::Init(const GameSpecifications& specifications, 
						 IInputState* inputState, RenderSystem* renderSystem, ITimeState* timeState)
{
	
	m_gameTime = new GameTime(timeState);
	m_gameInput = new GameInput(inputState);
	m_gameRenderManager = new GameRenderManager(renderSystem);
	m_sceneManager = new SceneManager();
	m_gameAssetResources = new GameAssetResources(specifications.p_pathToResourceImages,
												  specifications.p_pathToResourceFonts,
												  specifications.p_pathToResourceAudios);
	m_gameSpacesComputer = new GameSpacesComputer(renderSystem, specifications.p_worldWidthInWindow);
	m_gameSpacesComputer->Update();

	m_sceneManager->Init(specifications.p_startingScene);
}

void BilliardsGame::Cleanup()
{
	m_sceneManager->Cleanup();
}


void BilliardsGame::Update()
{
	m_gameSpacesComputer->Update();
	m_sceneManager->GetActiveScene()->Update();
	
	/*
	if (m_gameInput->GetKeyDown(KeyCode::MouseLeft))
	{
		printf("Click\n");
	}
	else if (GetSystems()->GetInputState()->GetKey(KeyCode::MouseLeft))
	{
		const Vector2<int> windowSize{ GetSystems()->GetRenderManager()->GetWindowSize() };
		GetSystems()->GetRenderManager()->DrawLine(Colors::Red, Vector2<int>{ 50, 50 }, windowSize - Vector2<int>{ 50, 50 });
	}
	*/
}

void BilliardsGame::Render()
{
	m_sceneManager->GetActiveScene()->Render();
}