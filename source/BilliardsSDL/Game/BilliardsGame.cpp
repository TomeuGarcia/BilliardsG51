#include "BilliardsGame.h"


BilliardsGame::BilliardsGame()
	: p_quitApplication(false), m_gameTime(nullptr), m_gameInput(nullptr), m_gameRenderManager(nullptr)
{
}

BilliardsGame::~BilliardsGame()
{
	delete m_gameTime;
	delete m_gameInput;
	delete m_gameRenderManager;
	delete m_sceneManager;
	delete m_gameAssetResources;
}

void BilliardsGame::Init(const GameSpecifications& specifications, 
						 IInputState* inputState, RenderSystem* renderSystem, ITimeState* timeState)
{
	
	m_gameTime = new GameTime(timeState);
	m_gameInput = new GameInput(inputState);
	m_gameRenderManager = new GameRenderManager(renderSystem);
	m_sceneManager = new SceneManager();
	m_gameAssetResources = new GameAssetResources(specifications.p_pathToResources);

	m_sceneManager->Init(specifications.p_startingScene);
}

void BilliardsGame::Cleanup()
{
	m_sceneManager->Cleanup();
}


void BilliardsGame::Update()
{
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