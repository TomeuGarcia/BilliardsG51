#include "Physics2DManager.h"


Physics2DManager* Physics2DManager::s_instance = nullptr;

Physics2DManager::Physics2DManager()
	: m_solver(Vector2<float>(0.0f, -9.8f)),
	m_rigidbodies(), m_rigidbodylessColliders(), m_activeCollisions()
{
	s_instance = this;

	m_rigidbodies.reserve(20);
	m_rigidbodylessColliders.reserve(20);
	m_activeCollisions.reserve(50);
}

Physics2DManager::~Physics2DManager()
{
	s_instance = nullptr;
}



Physics2DManager* Physics2DManager::GetInstance()
{
	return s_instance;
}



void Physics2DManager::ClearReferences()
{
	m_rigidbodies.clear();
	m_rigidbodylessColliders.clear();
	m_activeCollisions.clear();
}



void Physics2DManager::AddRigidbody(const std::shared_ptr<Rigidbody2D>& rigidbody)
{
	m_rigidbodies.emplace_back(rigidbody);
}

void Physics2DManager::AddRigidbodylessCollider(const std::shared_ptr<Collider2D>& collider)
{
	m_rigidbodylessColliders.emplace_back(collider);
}

void Physics2DManager::RemoveRigidbodylessCollider(const std::shared_ptr<Collider2D>& collider)
{
	for (auto it = m_rigidbodylessColliders.end() - 1; it != m_rigidbodylessColliders.begin(); --it)
	{
		if (it->get() == collider.get())
		{
			m_rigidbodylessColliders.erase(it);
			return;
		}
	}
}



void Physics2DManager::Update(const float& deltaTime)
{
	UpdateRigidbodies(deltaTime);
	UpdateCollisions();
}

void Physics2DManager::UpdateRigidbodies(const float& deltaTime)
{
	for (auto it = m_rigidbodies.begin(); it != m_rigidbodies.end(); ++it)
	{
		Rigidbody2D& rigidbody = **it;
		m_solver.Step(deltaTime, rigidbody);
		rigidbody.UpdatePosition();
		rigidbody.ApplyFriction();
		rigidbody.GetCollider()->UpdateShape();
	}
}

void Physics2DManager::UpdateRigidbodylessColliders()
{
	for (auto it = m_rigidbodylessColliders.begin(); it != m_rigidbodylessColliders.end(); ++it)
	{
		(*it)->UpdateShape();
	}
}

void Physics2DManager::UpdateCollisions()
{
}


