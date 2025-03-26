#include "Physics2DManager.h"




Physics2DManager* Physics2DManager::s_instance = nullptr;

Physics2DManager::Physics2DManager()
	: m_solver(Vector2<float>(0.0f, -9.8f)),
	m_circleCollidersGroup(),
	m_aaBoxCollidersGroup()
{
	s_instance = this;
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
	m_circleCollidersGroup.Clear();
	m_aaBoxCollidersGroup.Clear();
}



void Physics2DManager::AddCircleCollider(const std::shared_ptr<CircleCollider2D>& collider)
{
	m_circleCollidersGroup.AddCollider(collider, collider->HasRigidbody());
}

void Physics2DManager::AddAABoxCollider(const std::shared_ptr<AABoxCollider2D>&collider)
{
	m_aaBoxCollidersGroup.AddCollider(collider, collider->HasRigidbody());
}



void Physics2DManager::Update(const float& deltaTime)
{
	UpdateRigidbodies(deltaTime);
	UpdateRigidbodylessColliders();
	UpdateCollisions();
}


void Physics2DManager::UpdateRigidbodies(const float& deltaTime)
{
	std::vector<std::shared_ptr<CircleCollider2D>>& rigidbodyCircleColliders = 
		m_circleCollidersGroup.p_rigidbodyColliders;

	for (auto it = rigidbodyCircleColliders.begin(); it != rigidbodyCircleColliders.end(); ++it)
	{
		Rigidbody2D& rigidbody = *(*it)->GetRigidbody();
		m_solver.Step(deltaTime, rigidbody);
		rigidbody.UpdatePosition();
		rigidbody.ApplyFriction();
		(*it)->UpdateShape();
	}


	std::vector<std::shared_ptr<AABoxCollider2D>>& rigidbodyAABoxColliders = 
		m_aaBoxCollidersGroup.p_rigidbodyColliders;

	for (auto it = rigidbodyAABoxColliders.begin(); it != rigidbodyAABoxColliders.end(); ++it)
	{
		Rigidbody2D& rigidbody = *(*it)->GetRigidbody();
		m_solver.Step(deltaTime, rigidbody);
		rigidbody.UpdatePosition();
		rigidbody.ApplyFriction();
		(*it)->UpdateShape();
	}
}


void Physics2DManager::UpdateRigidbodylessColliders()
{
	std::vector<std::shared_ptr<CircleCollider2D>>& rigidbodyLESSCircleColliders =
		m_circleCollidersGroup.p_rigidbodylessColliders;

	for (auto it = rigidbodyLESSCircleColliders.begin(); it != rigidbodyLESSCircleColliders.end(); ++it)
	{
		(*it)->UpdateShape();
	}


	std::vector<std::shared_ptr<AABoxCollider2D>>& rigidbodyLESSAABoxColliders =
		m_aaBoxCollidersGroup.p_rigidbodylessColliders;

	for (auto it = rigidbodyLESSAABoxColliders.begin(); it != rigidbodyLESSAABoxColliders.end(); ++it)
	{
		(*it)->UpdateShape();
	}
}



//Rb circle check with Rb circle
//Rb circle check with Rb aaBox
//Rb circle check with circle
//Rb circle check with aaBox

//Rb aaBox check with Rb aaBox
//Rb aaBox check with circle
//Rb aaBox check with aaBox

void Physics2DManager::UpdateCollisions()
{
	std::vector<std::shared_ptr<CircleCollider2D>>& rigidbodyCircleColliders =
		m_circleCollidersGroup.p_rigidbodyColliders;
	std::vector<std::shared_ptr<AABoxCollider2D>>& rigidbodyAABoxColliders =
		m_aaBoxCollidersGroup.p_rigidbodyColliders;

	std::vector<std::shared_ptr<CircleCollider2D>>& rigidbodyLESSCircleColliders =
		m_circleCollidersGroup.p_rigidbodylessColliders;
	std::vector<std::shared_ptr<AABoxCollider2D>>& rigidbodyLESSAABoxColliders =
		m_aaBoxCollidersGroup.p_rigidbodylessColliders;

	
	for (auto itRbC = rigidbodyCircleColliders.begin(); itRbC != rigidbodyCircleColliders.end(); ++itRbC)
	{
		//Rb circle check with Rb circle
		for (auto itRbC_2 = itRbC + 1; itRbC_2 != rigidbodyCircleColliders.end(); ++itRbC_2)
		{
			CheckCircleWithCircle(itRbC->get(), itRbC_2->get());
		}

		//Rb circle check with Rb aaBox
		for (auto itRbB = rigidbodyAABoxColliders.begin(); itRbB != rigidbodyAABoxColliders.end(); ++itRbB)
		{
			CheckCircleWithAABox(itRbC->get(), itRbB->get());
		}


		//Rb circle check with circle
		for (auto itC = rigidbodyLESSCircleColliders.begin(); itC != rigidbodyLESSCircleColliders.end(); ++itC)
		{
			CheckCircleWithCircle(itRbC->get(), itC->get());
		}
		
		//Rb circle check with aaBox
		for (auto itB = rigidbodyLESSAABoxColliders.begin(); itB != rigidbodyLESSAABoxColliders.end(); ++itB)
		{
			//CheckCircleWithAABox(itRbC->get(), itB->get());
		}
	}


	for (auto itRbB = rigidbodyAABoxColliders.begin(); itRbB != rigidbodyAABoxColliders.end(); ++itRbB)
	{
		//Rb aaBox check with Rb aaBox
		for (auto itRbB_2 = itRbB + 1; itRbB_2 != rigidbodyAABoxColliders.end(); ++itRbB_2)
		{
			CheckAABoxWithAABox(itRbB->get(), itRbB_2->get());
		}
		

		//Rb aaBox check with circle
		for (auto itC = rigidbodyLESSCircleColliders.begin(); itC != rigidbodyLESSCircleColliders.end(); ++itC)
		{
			CheckAABoxWithCircle(itRbB->get(), itC->get());
		}

		//Rb aaBox check with aaBox
		for (auto itB = rigidbodyLESSAABoxColliders.begin(); itB != rigidbodyLESSAABoxColliders.end(); ++itB)
		{
			CheckAABoxWithAABox(itRbB->get(), itB->get());
		}
	}
}





void Physics2DManager::CheckCircleWithCircle(CircleCollider2D* circleColliderA, CircleCollider2D* circleColliderB)
{
	Vector2<float> abNormal;
	float halfIntersectDistance;
	const bool areColliding = CollisionHelper::ComputeCirclesCollisionWithOutputData(
		circleColliderA->GetShape(),circleColliderB->GetShape(),
		abNormal, halfIntersectDistance);
	
	if (areColliding)
	{
		CollisionHelper::ApplyContactCollision(circleColliderA->GetRigidbody(), abNormal, halfIntersectDistance);

		if (circleColliderB->HasRigidbody())
		{
			CollisionHelper::ApplyContactCollision(circleColliderB->GetRigidbody(), -abNormal, halfIntersectDistance);
		}
	}


	m_circleCollidersGroup.UpdateActiveCollision(circleColliderA, circleColliderB, areColliding);
}



void Physics2DManager::CheckCircleWithAABox(CircleCollider2D * circleColliderA, AABoxCollider2D * aaBoxColliderB)
{
	Vector2<float> aNormal, bNormal;
	float halfIntersectDistance;
	const bool areColliding = CollisionHelper::ComputeCircleAARectCollisionWithOutputData(
		circleColliderA->GetShape(), aaBoxColliderB->GetShape(),
		aNormal, bNormal, halfIntersectDistance);

	if (areColliding)
	{
		CollisionHelper::ApplyContactCollision(circleColliderA->GetRigidbody(), aNormal, halfIntersectDistance);

		if (aaBoxColliderB->HasRigidbody())
		{
			CollisionHelper::ApplyContactCollision(aaBoxColliderB->GetRigidbody(), bNormal, halfIntersectDistance);
		}
	}


	m_circleCollidersGroup.UpdateActiveCollision(circleColliderA, aaBoxColliderB, areColliding);
}




void Physics2DManager::CheckAABoxWithCircle(AABoxCollider2D* aaBoxColliderA, CircleCollider2D* circleColliderB)
{
	Vector2<float> aNormal, bNormal;
	float halfIntersectDistance;
	const bool areColliding = CollisionHelper::ComputeCircleAARectCollisionWithOutputData(
		circleColliderB->GetShape(), aaBoxColliderA->GetShape(),
		bNormal, aNormal, halfIntersectDistance);

	if (areColliding)
	{
		CollisionHelper::ApplyContactCollision(aaBoxColliderA->GetRigidbody(), aNormal, halfIntersectDistance);

		if (circleColliderB->HasRigidbody())
		{
			CollisionHelper::ApplyContactCollision(circleColliderB->GetRigidbody(), bNormal, halfIntersectDistance);
		}
	}

	m_aaBoxCollidersGroup.UpdateActiveCollision(aaBoxColliderA, circleColliderB, areColliding);
}



void Physics2DManager::CheckAABoxWithAABox(AABoxCollider2D * aaBoxColliderA, AABoxCollider2D * aaBoxColliderB)
{
	Vector2<float> aNormal;
	float halfIntersectDistance;
	const bool areColliding = CollisionHelper::ComputeAARectsCollisionWithOutputData(
		aaBoxColliderA->GetShape(), aaBoxColliderA->GetShape(),
		aNormal, halfIntersectDistance);

	if (areColliding)
	{
		CollisionHelper::ApplyContactCollision(aaBoxColliderA->GetRigidbody(), aNormal, halfIntersectDistance);

		if (aaBoxColliderB->HasRigidbody())
		{
			CollisionHelper::ApplyContactCollision(aaBoxColliderB->GetRigidbody(), -aNormal, halfIntersectDistance);
		}
	}

	m_aaBoxCollidersGroup.UpdateActiveCollision(aaBoxColliderA, aaBoxColliderB, areColliding);
}
