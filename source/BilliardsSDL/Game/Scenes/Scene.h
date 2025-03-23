#pragma once
#include <vector>

#include "../GameObjects/GameObject.h"


class Scene
{
public:
	Scene();
	~Scene();

	void Init();
	void Cleanup();


protected:
	virtual void CreateGameObjects() = 0;


private:
	std::vector<GameObject> m_gameObjects;


};