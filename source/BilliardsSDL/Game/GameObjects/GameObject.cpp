#include "GameObject.h"


GameObject::GameObject(const Vector2<float>& position, const std::string& name)
	: m_transform(position), m_name(name), m_behaviours()
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



Transform* const GameObject::GetTransform()
{
	return &m_transform;
}

const std::string& GameObject::GetName()
{
	return m_name;
}

const std::vector<std::shared_ptr<Behaviour>>& GameObject::GetBehaviours()
{
	return m_behaviours;
}

