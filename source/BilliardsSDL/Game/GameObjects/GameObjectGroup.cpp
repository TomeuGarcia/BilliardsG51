#include "GameObjectGroup.h"

GameObjectGroup::GameObjectGroup(const int& startingCapacity)
	: m_gameObjects()
{
	m_gameObjects.reserve(startingCapacity);
}

void GameObjectGroup::Add(GameObject* gameObject)
{
	m_gameObjects.emplace_back(gameObject);
}

void GameObjectGroup::SetActive(const bool& active)
{
	for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
	{
		(*it)->SetActive(active);
	}
}
