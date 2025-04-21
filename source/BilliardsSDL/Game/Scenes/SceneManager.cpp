#include "SceneManager.h"

SceneManager* SceneManager::s_sceneManager = nullptr;

SceneManager::SceneManager()
	: m_activeScene(nullptr)
{
	s_sceneManager = this;
}

SceneManager::~SceneManager()
{
	m_activeScene = nullptr;
}



SceneManager* SceneManager::GetInstance()
{
	return s_sceneManager;
}



void SceneManager::Init(const SceneName startingSceneName)
{
	Scene* startingScene{ MakeNewSceneByName(startingSceneName) };
	InitNewActiveScene(startingScene);
}

void SceneManager::Cleanup()
{
	CleanupActiveScene();
}

void SceneManager::UpdateLoading()
{
	if (m_queuedLoadScene)
	{
		LoadQueuedScene();
		m_queuedLoadScene = false;
	}
}

Scene* SceneManager::GetActiveScene() const
{
	return m_activeScene;
}

void SceneManager::LoadScene(const SceneName sceneName)
{
	m_queuedLoadScene = true;
	m_queuedLoadSceneName = sceneName;
}



void SceneManager::LoadQueuedScene()
{
	DoLoadScene(m_queuedLoadSceneName);
}

void SceneManager::DoLoadScene(const SceneName sceneName)
{
	Scene* newScene{ MakeNewSceneByName(sceneName) };
	CleanupActiveScene();
	InitNewActiveScene(newScene);
}

Scene* SceneManager::MakeNewSceneByName(const SceneName sceneName)
{
	switch (sceneName)
	{
		case SceneName::MainMenu:
			return new MainMenuScene();
			break;
		case SceneName::Ranking:
			return new RankingScene();
			break;
		case SceneName::BilliardGame:
			return new BilliardsGameScene();
			break;
		case SceneName::TitleScreenshot:
			return new TitleScreenshotScene();
			break;
		default:
			return nullptr;
			break;
	}
}



void SceneManager::InitNewActiveScene(Scene* newScene)
{
	m_activeScene = newScene;
	m_activeScene->Init();
}

void SceneManager::CleanupActiveScene()
{
	m_activeScene->Cleanup();
	delete m_activeScene;
}
