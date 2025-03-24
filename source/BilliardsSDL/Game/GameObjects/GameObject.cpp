#include "GameObject.h"


GameObject::GameObject(const Vector2<int>& position)
	: m_transform(position)/*, m_renderer(nullptr)*/
{
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
}



Transform* const GameObject::GetTransform()
{
	return &m_transform;
}



bool GameObject::HasAttachedRenderer() const
{
	return m_renderer != nullptr;
}

Renderer* GameObject::GetRenderer() const
{
	return &(*m_renderer);
}

void GameObject::AttachRenderer(const std::shared_ptr<Renderer>& renderer)
{
	m_renderer = renderer;
}


