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
	Start();
}

void Scene::Cleanup()
{
	m_gameObjects.clear();
	GameRenderManager::GetInstance()->ClearRenderQueue();
}

void Scene::Update()
{
	for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
	{
		it->Update();
	}
}

void Scene::Render()
{
	GameRenderManager::GetInstance()->DrawRendererQueue();
}



GameObject* Scene::CreateGameObject(const Vector2<float>& position)
{
	m_gameObjects.emplace_back(position);
	return &(*m_gameObjects.rbegin());
}

std::shared_ptr<Image> Scene::CreateImageComponent(GameObject* owner, const ImageResourceData& resourceData, const Vector2<float>& size)
{	
	std::shared_ptr<Image> image = std::make_shared<Image>(owner, size);
	image->Init(*GameRenderManager::GetInstance(), resourceData);

	GameRenderManager::GetInstance()->AddToRenderQueue(image);

	return image;
}

std::shared_ptr<Text> Scene::CreateTextComponent(GameObject* owner, const TextResourceData& resourceData,
												 const std::string& textString, const int pointSize)
{
	std::shared_ptr<Text> text = std::make_shared<Text>(owner, textString, pointSize);
	text->Init(*GameRenderManager::GetInstance(), resourceData);

	GameRenderManager::GetInstance()->AddToRenderQueue(text);

	return text;
}
