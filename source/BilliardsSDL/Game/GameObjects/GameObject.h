#pragma once
#include <memory>
#include <vector>
#include "Transform.h"
#include "Behaviours/Behaviour.h"


class GameObject
{
public:
	GameObject(const Vector2<float>& position, const std::string& name);
	virtual ~GameObject();

	void Start();
	void Update();
	void OnDestroy();

	void AttachBehaviour(const std::shared_ptr<Behaviour>& behaviour);

public:
	Transform* const GetTransform();	
	const std::string& GetName();
	const std::vector<std::shared_ptr<Behaviour>>& GetBehaviours();
	
private:
	std::string m_name;
	Transform m_transform;	
	std::vector<std::shared_ptr<Behaviour>> m_behaviours;
};