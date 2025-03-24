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

Scene* SceneManager::GetActiveScene() const
{
	return m_activeScene;
}

void SceneManager::LoadScene(const SceneName sceneName)
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
			return new EmptyScene(Colors::Red);
			break;
		case SceneName::Ranking:
			return new EmptyScene(Colors::Green);
			break;
		case SceneName::BilliardGame:
			return new EmptyScene(Colors::Blue);
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
