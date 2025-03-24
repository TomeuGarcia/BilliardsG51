#pragma once
#include <memory>
#include <vector>
#include "Transform.h"
#include "Behaviours/Behaviour.h"


class GameObject
{
public:
	GameObject(const Vector2<float>& position);
	virtual ~GameObject();

	virtual void Start();
	virtual void Update();

	void AttachBehaviour(const std::shared_ptr<Behaviour>& behaviour);

public:
	Transform* const GetTransform();	
	const std::vector<std::shared_ptr<Behaviour>>& GetBehaviours();

private:
	Transform m_transform;	
	std::vector<std::shared_ptr<Behaviour>> m_behaviours;
};