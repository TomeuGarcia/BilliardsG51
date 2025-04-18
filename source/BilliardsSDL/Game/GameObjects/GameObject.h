#pragma once
#include <memory>
#include <vector>
#include <string_view>
#include "Transform.h"
#include "Behaviours/Behaviour.h"
#include "GameObjectTag.h"


class GameObject
{
public:
	GameObject(const Vector2<float>& position, const std::string& name);
	virtual ~GameObject();

	void Start();
	void Update();
	void OnDestroy();

	void AttachBehaviour(const std::shared_ptr<Behaviour>& behaviour);

	void SetActive(const bool& active);
	bool IsActive() const;

	void AddTag(const GameObjectTag& tag);
	bool HasTag(const GameObjectTag& tag);

public:
	Transform* const GetTransform();	
	std::string_view GetName();
	const std::vector<std::shared_ptr<Behaviour>>& GetBehaviours();
	
private:
	std::string m_name;
	Transform m_transform;	
	std::vector<std::shared_ptr<Behaviour>> m_behaviours;
	bool m_active;
	GameObjectTag m_tags;
};