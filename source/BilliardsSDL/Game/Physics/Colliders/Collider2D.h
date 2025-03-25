#pragma once
#include "../../GameObjects/GameObject.h"

class Collider2D
{
public:
	Collider2D(GameObject* gameOject);
	~Collider2D();

	GameObject* GetGameObject();

public:
	virtual void UpdateShape() = 0;


private:
	GameObject* m_gameObject;
};