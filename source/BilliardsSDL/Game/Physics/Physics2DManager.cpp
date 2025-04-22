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
		if (!rigidbody.GetIsEnabled())
		{
			continue;
		}

		m_solver.Step(deltaTime, rigidbody);
		rigidbody.UpdatePosition();
		rigidbody.ApplyFriction(deltaTime);
		(*it)->UpdateShape();
	}


	std::vector<std::shared_ptr<AABoxCollider2D>>& rigidbodyAABoxColliders = 
		m_aaBoxCollidersGroup.p_rigidbodyColliders;

	for (auto it = rigidbodyAABoxColliders.begin(); it != rigidbodyAABoxColliders.end(); ++it)
	{
		Rigidbody2D& rigidbody = *(*it)->GetRigidbody();
		if (!rigidbody.GetIsEnabled())
		{
			continue;
		}

		m_solver.Step(deltaTime, rigidbody);
		rigidbody.UpdatePosition();
		rigidbody.ApplyFriction(deltaTime);
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
		if (!itRbC->get()->GetRigidbody()->GetIsEnabled())
		{
			continue;
		}

		//Rb circle check with Rb circle
		for (auto itRbC_2 = itRbC + 1; itRbC_2 != rigidbodyCircleColliders.end(); ++itRbC_2)
		{
			if (!itRbC_2->get()->GetRigidbody()->GetIsEnabled())
			{
				continue;
			}
			CheckCircleWithCircle(itRbC->get(), itRbC_2->get());
		}

		//Rb circle check with Rb aaBox
		for (auto itRbB = rigidbodyAABoxColliders.begin(); itRbB != rigidbodyAABoxColliders.end(); ++itRbB)
		{
			if (!itRbB->get()->GetRigidbody()->GetIsEnabled())
			{
				continue;
			}
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
			CheckCircleWithAABox(itRbC->get(), itB->get());
		}
	}


	for (auto itRbB = rigidbodyAABoxColliders.begin(); itRbB != rigidbodyAABoxColliders.end(); ++itRbB)
	{
		if (!itRbB->get()->GetRigidbody()->GetIsEnabled())
		{
			continue;
		}

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
	float intersectDistance;
	const bool areColliding = CollisionHelper::ComputeCirclesCollisionWithOutputData(
		circleColliderA->GetShape(),circleColliderB->GetShape(),
		abNormal, intersectDistance);


	bool wereAlreadyColliding;
	m_circleCollidersGroup.UpdateActiveCollision(circleColliderA, circleColliderB, areColliding, wereAlreadyColliding);
	if (wereAlreadyColliding)
	{
		return;
	}

	
	const bool bothAreColliders = !circleColliderA->GetIsTrigger() && !circleColliderB->GetIsTrigger();	
	if (areColliding && bothAreColliders)
	{
		ResolveCollision(circleColliderA->GetRigidbody(), 
						 circleColliderB->GetRigidbody(), circleColliderB->HasRigidbody(),
						 abNormal, intersectDistance);
	}	
}



void Physics2DManager::CheckCircleWithAABox(CircleCollider2D* circleColliderA, AABoxCollider2D* aaBoxColliderB)
{
	Vector2<float> abNormal;
	float intersectDistance;
	const bool areColliding = CollisionHelper::ComputeCircleAARectCollisionWithOutputData(
		circleColliderA->GetShape(), aaBoxColliderB->GetShape(),
		abNormal, intersectDistance);


	bool wereAlreadyColliding;
	m_circleCollidersGroup.UpdateActiveCollision(circleColliderA, aaBoxColliderB, areColliding, wereAlreadyColliding);
	if (wereAlreadyColliding)
	{
		return;
	}


	const bool bothAreColliders = !circleColliderA->GetIsTrigger() && !aaBoxColliderB->GetIsTrigger();
	if (areColliding && bothAreColliders)
	{
		ResolveCollision(circleColliderA->GetRigidbody(),
						 aaBoxColliderB->GetRigidbody(), aaBoxColliderB->HasRigidbody(),
						 abNormal, intersectDistance);
	}
}




void Physics2DManager::CheckAABoxWithCircle(AABoxCollider2D* aaBoxColliderA, CircleCollider2D* circleColliderB)
{
	Vector2<float> abNormal;
	float intersectDistance;
	const bool areColliding = CollisionHelper::ComputeCircleAARectCollisionWithOutputData(
		circleColliderB->GetShape(), aaBoxColliderA->GetShape(),
		abNormal, intersectDistance);


	bool wereAlreadyColliding;
	m_aaBoxCollidersGroup.UpdateActiveCollision(aaBoxColliderA, circleColliderB, areColliding, wereAlreadyColliding);
	if (wereAlreadyColliding)
	{
		return;
	}


	const bool bothAreColliders = !aaBoxColliderA->GetIsTrigger() && !circleColliderB->GetIsTrigger();
	if (areColliding && bothAreColliders)
	{
		ResolveCollision(aaBoxColliderA->GetRigidbody(),
						 circleColliderB->GetRigidbody(), circleColliderB->HasRigidbody(),
						 -abNormal, intersectDistance);
	}
}



void Physics2DManager::CheckAABoxWithAABox(AABoxCollider2D* aaBoxColliderA, AABoxCollider2D* aaBoxColliderB)
{
	Vector2<float> aNormal;
	float intersectDistance;
	const bool areColliding = CollisionHelper::ComputeAARectsCollisionWithOutputData(
		aaBoxColliderA->GetShape(), aaBoxColliderA->GetShape(),
		aNormal, intersectDistance);


	bool wereAlreadyColliding;
	m_aaBoxCollidersGroup.UpdateActiveCollision(aaBoxColliderA, aaBoxColliderB, areColliding, wereAlreadyColliding);
	if (wereAlreadyColliding)
	{
		return;
	}


	const bool bothAreColliders = !aaBoxColliderA->GetIsTrigger() && !aaBoxColliderB->GetIsTrigger();
	if (areColliding && bothAreColliders)
	{
		const bool otherAlsoHasRigidbody = aaBoxColliderB->HasRigidbody();
		intersectDistance = otherAlsoHasRigidbody ? intersectDistance / 2 : intersectDistance;

		CollisionHelper::ApplyContactCollision(aaBoxColliderA->GetRigidbody(), aNormal, intersectDistance);

		if (otherAlsoHasRigidbody)
		{
			CollisionHelper::ApplyContactCollision(aaBoxColliderB->GetRigidbody(), -aNormal, intersectDistance);
		}
	}
}



void Physics2DManager::ResolveCollision(Rigidbody2D* rigidbodyA, Rigidbody2D* rigidbodyB, const bool& bAlsoHasRigidbody,
	const Vector2<float> abNormal, float& intersectDistance)
{
	intersectDistance = bAlsoHasRigidbody ? intersectDistance / 2 : intersectDistance;
	
	Vector2<float> motionForceA = rigidbodyA->GetMomentum();
	Vector2<float> motionForceB = bAlsoHasRigidbody ? rigidbodyB->GetMomentum() : Vector2<float>::Zero();

	if (rigidbodyA->IsAtRest())
	{
		CollisionHelper::ApplyCollisionForceOnRestingBody(rigidbodyA, motionForceB, abNormal);
	}
	else
	{
		CollisionHelper::ApplyContactCollision(rigidbodyA, abNormal, intersectDistance);
	}

	if (bAlsoHasRigidbody)
	{
		if (rigidbodyB->IsAtRest())
		{
			CollisionHelper::ApplyCollisionForceOnRestingBody(rigidbodyB, motionForceA, -abNormal);
		}
		else
		{
			CollisionHelper::ApplyContactCollision(rigidbodyB, -abNormal, intersectDistance);
		}
	}
}








// Probing functions
std::list<Collider2D*> Physics2DManager::CircleOverlap(const Vector2<float>& position, const float& radius)
{
	std::list<Collider2D*> overlappedColliders{};

	const Circle overlapCircle(position, radius);
	Vector2<float> normal;
	float distance;

	std::vector<std::shared_ptr<CircleCollider2D>>& rigidbodyCircleColliders =
		m_circleCollidersGroup.p_rigidbodyColliders;
	std::vector<std::shared_ptr<AABoxCollider2D>>& rigidbodyAABoxColliders =
		m_aaBoxCollidersGroup.p_rigidbodyColliders;

	std::vector<std::shared_ptr<CircleCollider2D>>& rigidbodyLESSCircleColliders =
		m_circleCollidersGroup.p_rigidbodylessColliders;
	std::vector<std::shared_ptr<AABoxCollider2D>>& rigidbodyLESSAABoxColliders =
		m_aaBoxCollidersGroup.p_rigidbodylessColliders;


	for (auto it = rigidbodyCircleColliders.begin(); it != rigidbodyCircleColliders.end(); ++it)
	{
		if (!(*it)->GetRigidbody()->GetIsEnabled())
		{
			continue;
		}

		if (CollisionHelper::ComputeCirclesCollisionWithOutputData(overlapCircle, (*it)->GetShape(), normal, distance))
		{
			overlappedColliders.push_back(it->get());
		}
	}

	for (auto it = rigidbodyLESSCircleColliders.begin(); it != rigidbodyLESSCircleColliders.end(); ++it)
	{
		if (CollisionHelper::ComputeCirclesCollisionWithOutputData(overlapCircle, (*it)->GetShape(), normal, distance))
		{
			overlappedColliders.push_back(it->get());
		}
	}

	for (auto it = rigidbodyAABoxColliders.begin(); it != rigidbodyAABoxColliders.end(); ++it)
	{
		if (!(*it)->GetRigidbody()->GetIsEnabled())
		{
			continue;
		}

		if (CollisionHelper::ComputeCircleAARectCollisionWithOutputData(overlapCircle, (*it)->GetShape(), normal, distance))
		{
			overlappedColliders.push_back(it->get());
		}
	}

	for (auto it = rigidbodyLESSAABoxColliders.begin(); it != rigidbodyLESSAABoxColliders.end(); ++it)
	{
		if (CollisionHelper::ComputeCircleAARectCollisionWithOutputData(overlapCircle, (*it)->GetShape(), normal, distance))
		{
			overlappedColliders.push_back(it->get());
		}
	}

	return overlappedColliders;
}



std::vector<CollisionHit2D> Physics2DManager::Raycast(const Line<float>& raySegment)
{
	std::vector<CollisionHit2D> hits{};
	hits.reserve(10);
	Vector2<float> pointInLine;
	float distance;

	std::vector<std::shared_ptr<CircleCollider2D>>& rigidbodyCircleColliders =
		m_circleCollidersGroup.p_rigidbodyColliders;
	std::vector<std::shared_ptr<AABoxCollider2D>>& rigidbodyAABoxColliders =
		m_aaBoxCollidersGroup.p_rigidbodyColliders;

	std::vector<std::shared_ptr<CircleCollider2D>>& rigidbodyLESSCircleColliders =
		m_circleCollidersGroup.p_rigidbodylessColliders;
	std::vector<std::shared_ptr<AABoxCollider2D>>& rigidbodyLESSAABoxColliders =
		m_aaBoxCollidersGroup.p_rigidbodylessColliders;


	for (auto it = rigidbodyCircleColliders.begin(); it != rigidbodyCircleColliders.end(); ++it)
	{		
		if (!(*it)->GetRigidbody()->GetIsEnabled())
		{
			continue;
		}

		if (Math::ComputeLineToCircleDistance(raySegment, (*it)->GetShape(), pointInLine, distance))
		{
			hits.emplace_back(it->get(), pointInLine, Vector2<float>::Distance(pointInLine, raySegment.GetOrigin()));
		}
	}

	for (auto it = rigidbodyLESSCircleColliders.begin(); it != rigidbodyLESSCircleColliders.end(); ++it)
	{
		if (Math::ComputeLineToCircleDistance(raySegment, (*it)->GetShape(), pointInLine, distance))
		{
			hits.emplace_back(it->get(), pointInLine, Vector2<float>::Distance(pointInLine, raySegment.GetOrigin()));
		}
	}

	for (auto it = rigidbodyAABoxColliders.begin(); it != rigidbodyAABoxColliders.end(); ++it)
	{
		if (!(*it)->GetRigidbody()->GetIsEnabled())
		{
			continue;
		}

		if (Math::ComputeLineToAARectDistance(raySegment, (*it)->GetShape(), pointInLine, distance))
		{
			hits.emplace_back(it->get(), pointInLine, distance);
		}
	}

	for (auto it = rigidbodyLESSAABoxColliders.begin(); it != rigidbodyLESSAABoxColliders.end(); ++it)
	{
		if (Math::ComputeLineToAARectDistance(raySegment, (*it)->GetShape(), pointInLine, distance))
		{
			hits.emplace_back(it->get(), pointInLine, distance);
		}
	}

	return hits;
}

bool Physics2DManager::RaycastFirstHit(const Line<float>& raySegment, CollisionHit2D& outHit)
{
	const std::vector<CollisionHit2D> hits = Raycast(raySegment);
	const size_t hitsCount = hits.size();

	if (hitsCount < 1)
	{
		return false;
	}

	outHit = hits.front();
	for (size_t i = 1; i < hitsCount; ++i)
	{
		const CollisionHit2D& itHit = hits[i];
		if (outHit.distanceFromOrigin > itHit.distanceFromOrigin)
		{
			outHit = itHit;
		}
	}

	return true;
}
