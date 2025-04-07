#include "Scene.h"


Scene::Scene()
	: m_gameObjects(),
	m_createUtilities(&m_gameObjects),
	m_customPrefabs(&m_createUtilities)
{
	m_gameObjects.reserve(40); // For some reason this sets the maximum amount of possible gameObjects...
}

Scene::~Scene()
{
}

void Scene::Init()
{
	CreateGameObjects();
	Start();
}

void Scene::Cleanup()
{
	for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
	{
		it->OnDestroy();
	}

	m_gameObjects.clear();
	GameRenderManager::GetInstance()->ClearRenderQueue();
	Physics2DManager::GetInstance()->ClearReferences();
	GameTweener::GetInstance()->Clear();
}


void Scene::Start()
{
	for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
	{
		it->Start();
	}

	DoStart();
}

void Scene::Update()
{
	for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
	{
		it->Update();
	}

	DoUpdate();
}

void Scene::Render()
{
	GameRenderManager::GetInstance()->DrawRendererQueue();
}



SceneCreateUtilities& Scene::GetCreateUtilities()
{
	return m_createUtilities;
}

CustomPrefabUtilities& Scene::GetPrefabUtilities()
{
	return m_customPrefabs;
}
