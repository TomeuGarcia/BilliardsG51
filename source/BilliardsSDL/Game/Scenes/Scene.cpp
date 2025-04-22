#include "Scene.h"


Scene::Scene()
	: m_gameObjectsBuffer(40),
	m_createUtilities(&m_gameObjectsBuffer),
	m_customPrefabs(&m_createUtilities)
{	
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
	m_gameObjectsBuffer.IterateAll([](GameObject& gameObject, const size_t& i)
		{
			gameObject.OnDestroy();
		}
	);

	OnDestroy();

	m_gameObjectsBuffer.Clear();
	GameRenderManager::GetInstance()->ClearRenderQueue();
	Physics2DManager::GetInstance()->ClearReferences();
	UICaster::GetInstance()->ClearSelectables();
	GameTweener::GetInstance()->Clear();
}


void Scene::Start()
{
	m_gameObjectsBuffer.IterateAll([](GameObject& gameObject, const size_t& i)
		{
			gameObject.Start();
		}
	);

	DoStart();
}

void Scene::Update()
{
	m_gameObjectsBuffer.IterateAll([](GameObject& gameObject, const size_t& i)
		{
			if (gameObject.IsActive())
			{
				gameObject.Update();
			}
		}
	);

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
