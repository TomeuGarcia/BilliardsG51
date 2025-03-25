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
	Physics2DManager::GetInstance()->ClearReferences();
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



std::shared_ptr<Rigidbody2D> Scene::CreateRigidbodyComponent(GameObject* gameObject,
	const std::shared_ptr<PhysicMaterial>& physicMaterial,
	const float& mass, const float& gravityScale)
{
	std::shared_ptr<Rigidbody2D> rigidbody = std::make_shared<Rigidbody2D>(gameObject, physicMaterial, mass, gravityScale);
	return rigidbody;
}

std::shared_ptr<CircleCollider2D> Scene::CreateCircleColliderComponent(GameObject* owner, Rigidbody2D* optionalRigidbody, const float& radius)
{
	std::shared_ptr<CircleCollider2D> circleCollider = std::make_shared<CircleCollider2D>(owner, optionalRigidbody, radius);

	Physics2DManager::GetInstance()->AddCircleCollider(circleCollider);

	return circleCollider;
}

std::shared_ptr<AABoxCollider2D> Scene::CreateAABoxColliderComponent(GameObject* owner, Rigidbody2D* optionalRigidbody, const Vector2<float>& size)
{
	std::shared_ptr<AABoxCollider2D> aaBoxCollider = std::make_shared<AABoxCollider2D>(owner, optionalRigidbody, size);

	Physics2DManager::GetInstance()->AddAABoxCollider(aaBoxCollider);

	return aaBoxCollider;
}
