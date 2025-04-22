#include "GameObject.h"


GameObject::GameObject(const Vector2<float>& position, const std::string& name)
	: m_transform(position), m_name(name), m_behaviours(), m_active(true),
	m_tags(GameObjectTag::None)
{
	m_behaviours.reserve(1);
}

GameObject::~GameObject()
{
}



void GameObject::Start()
{
	for (auto it = m_behaviours.begin(); it != m_behaviours.end(); ++it)
	{
		(*it)->Start();
	}
}

void GameObject::Update()
{
	for (auto it = m_behaviours.begin(); it != m_behaviours.end(); ++it)
	{
		(*it)->Update();
	}
}

void GameObject::OnDestroy()
{
	for (auto it = m_behaviours.begin(); it != m_behaviours.end(); ++it)
	{
		(*it)->OnDestroy();
	}
}



void GameObject::AttachBehaviour(const std::shared_ptr<Behaviour>& behaviour)
{
	m_behaviours.emplace_back(behaviour);
}

void GameObject::SetActive(const bool& active)
{
	m_active = active;
}

bool GameObject::IsActive() const
{
	return m_active;
}



void GameObject::AddTag(const GameObjectTag& tag)
{
	m_tags |= tag;
}

bool GameObject::HasTag(const GameObjectTag& tag)
{
	return (m_tags & tag) == tag;
}




Transform* const GameObject::GetTransform()
{
	return &m_transform;
}

std::string_view GameObject::GetName()
{
	return m_name;
}

const std::vector<std::shared_ptr<Behaviour>>& GameObject::GetBehaviours()
{
	return m_behaviours;
}

