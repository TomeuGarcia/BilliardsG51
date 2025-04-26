#pragma once
#include <memory>
#include <vector>
#include <string_view>
#include <type_traits>
#include <concepts>

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

	//template<typename T>
	//typename std::enable_if<std::is_base_of<Behaviour, T>::value, bool>::type
	template<std::derived_from<Behaviour> T>
	bool TryGetBehaviour(T*& out) const;

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



//template<typename T>
//typename std::enable_if<std::is_base_of<Behaviour, T>::value, bool>::type
template<std::derived_from<Behaviour> T>
inline bool GameObject::TryGetBehaviour(T*& out) const
{
	for (auto it = m_behaviours.begin(); it != m_behaviours.end(); ++it)
	{
		out = dynamic_cast<T*>(it->get());
		if (out != nullptr)
		{
			return true;
		}
	}

	return false;
}
