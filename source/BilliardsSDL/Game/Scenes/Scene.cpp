#include "Scene.h"


Scene::Scene()
	: m_gameObjects(),
	m_createUtilities(&m_gameObjects),
	m_customPrefabs(&m_createUtilities)
{
	m_gameObjects.reserve(80); // If this is resized, the old GameObject* references are lost...
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
	OnDestroy();

	m_gameObjects.clear();
	GameRenderManager::GetInstance()->ClearRenderQueue();
	Physics2DManager::GetInstance()->ClearReferences();
	UICaster::GetInstance()->ClearSelectables();
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
		if (it->IsActive())
		{
			it->Update();
		}		
	}

	DoUpdate();
}

void Scene::OnDestroy()
{
}


SceneCreateUtilities& Scene::GetCreateUtilities()
{
	return m_createUtilities;
}

CustomPrefabUtilities& Scene::GetPrefabUtilities()
{
	return m_customPrefabs;
}
