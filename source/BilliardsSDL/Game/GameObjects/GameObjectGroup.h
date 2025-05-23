#pragma once
#include "GameObject.h"



class GameObjectGroup
{
public:
	GameObjectGroup(const int& startingCapacity);

	void Add(GameObject* gameObject);
	void Add(const GameObjectGroup& other);

	void SetActive(const bool& active);


private:
	std::vector<GameObject*> m_gameObjects;
};