#pragma once
#include "../../GameObjects/GameObject.h"
#include "../Rigidbodies/Rigidbody2D.h"


class Collider2D
{
public:
	Collider2D(GameObject* gameOject, Rigidbody2D* optionalRigidbody, const bool& isTrigger);
	~Collider2D();

	GameObject* GetGameObject() const;
	bool HasRigidbody();
	Rigidbody2D* GetRigidbody() const;
	bool GetIsTrigger() const;


public:
	virtual void UpdateShape() = 0;


private:
	GameObject* m_gameObject;
	Rigidbody2D* m_rigidbody;
	bool m_isTrigger;
};