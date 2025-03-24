#include "Scene.h"


Scene::Scene()
	: m_gameObjects()
{
	m_gameObjects.reserve(20);
}

Scene::~Scene()
{
}

void Scene::Init()
{
	CreateGameObjects();
	SetupGameObjectRenderers();
	Start();
}

void Scene::Cleanup()
{
	m_gameObjects.clear();
	GameRenderManager::GetInstance()->ClearRenderQueue();
}

void Scene::Update()
{
	printf("%f\n", GameTime::GetInstance()->GetTime());
}

void Scene::Render()
{
	GameRenderManager::GetInstance()->DrawRendererQueue();
}



GameObject* Scene::CreateGameObject(const Vector2<int>& position)
{
	m_gameObjects.emplace_back(position);
	return &(*m_gameObjects.rbegin());
}

std::shared_ptr<Image> Scene::CreateImageComponent(GameObject* owner, const ImageResourceData& resourceData, const Vector2<int>& size)
{
	std::shared_ptr<Image> backgroundImage = std::make_shared<Image>(owner->GetTransform(), size);
	backgroundImage->Init(*GameRenderManager::GetInstance(), resourceData);
	owner->AttachRenderer(backgroundImage);

	return backgroundImage;
}



void Scene::SetupGameObjectRenderers()
{
	std::vector<Renderer*> renderersInScene{};
	renderersInScene.reserve(m_gameObjects.size());

	for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
	{
		if (it->HasAttachedRenderer())
		{
			renderersInScene.emplace_back(it->GetRenderer());
		}
	}

	GameRenderManager::GetInstance()->FillRenderQueue(renderersInScene);	
}
