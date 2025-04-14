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

void GameObjectGroup::Add(const GameObjectGroup& other)
{
	for (auto it = other.m_gameObjects.begin(); it != other.m_gameObjects.end(); ++it)
	{
		Add(*it);
	}
}


void GameObjectGroup::SetActive(const bool& active)
{
	for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
	{
		(*it)->SetActive(active);
	}
}
