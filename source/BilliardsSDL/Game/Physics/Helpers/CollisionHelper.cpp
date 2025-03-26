#include "CollisionHelper.h"

namespace CollisionHelper
{
	bool ComputeCirclesCollisionWithOutputData(const Circle& circleA, const Circle& circleB,
		Vector2<float>& outNormalForAB, float& outHalfIntersectionDistance)
	{
		const Vector2<float> ab = circleB.p_position - circleA.p_position;
		const float distanceBetweenCircles = ab.Length();		
		outNormalForAB = ab / distanceBetweenCircles;

		const float radiusSum = circleA.GetRadius() + circleB.GetRadius();
		outHalfIntersectionDistance = (radiusSum - distanceBetweenCircles) / 2.0f;

		return distanceBetweenCircles < radiusSum;
	}


	bool ComputeCircleAARectCollisionWithOutputData(const Circle& circleA, const Rect<float>& aaRectB,
		Vector2<float>& outNormalForA, Vector2<float>& outNormalForB, float& outHalfIntersectionDistance)
	{
		const Vector2<float> rectCenter = aaRectB.GetCenterPosition();
		const Vector2<float> ab = rectCenter - circleA.p_position;
		const float distanceBetweenRectAndCircle= ab.Length();
			
		outNormalForB = ab / distanceBetweenRectAndCircle;

		const bool circleIsInside = Math::IsPointInsideRect(aaRectB, circleA.p_position);

		if (circleIsInside)
		{
			const Vector2<float> rectHalfSize = aaRectB.GetHalfSize();
			outHalfIntersectionDistance = (Vector2<float>::Dot(rectHalfSize, outNormalForB)) / 2.0f;
		}


		float distanceToEdge;
		const Line<float>& closestRectEdgeLine = Math::GetClosestRectEdgeLineToPoint(circleA.p_position, aaRectB, distanceToEdge);
		Vector2<float> perpendicularPointOnEdge = closestRectEdgeLine.GetPointAtRatio(0.5f);
		outNormalForA = (perpendicularPointOnEdge - rectCenter).Normalized();


		if (circleIsInside)
		{
			return true;
		}


		// from here on circle is outside
		const float distanceEdgeToCircle = distanceToEdge - circleA.GetRadius();
		bool collideFromOutside = distanceEdgeToCircle < distanceToEdge;

		if (!collideFromOutside)
		{
			return false;
		}

		outHalfIntersectionDistance = distanceEdgeToCircle / 2.0f;
		return true;
	}



	bool ComputeAARectsCollisionWithOutputData(const Rect<float>& aaRectA, const Rect<float>& aaRectB,
		Vector2<float>& outNormalForAB, float& outHalfIntersectionDistance)
	{
		if (!Math::AreAARectsIntersecting(aaRectA, aaRectB))
		{
			return false;
		}


		float distanceToEdge;
		const Line<float>& closestRectBEdgeLine = Math::GetClosestRectEdgeLineToPoint(aaRectA.GetCenterPosition(), aaRectB, distanceToEdge);
		const Vector2<float> rectaBCenter = aaRectB.GetCenterPosition();

		Vector2<float> perpendicularPointOnEdge = closestRectBEdgeLine.GetPointAtRatio(0.5f);

		outNormalForAB = (perpendicularPointOnEdge - rectaBCenter).Normalized();

		outHalfIntersectionDistance = distanceToEdge / 2.0f;

		return true;
	}



	void ApplyContactCollision(Rigidbody2D* rigidbody, const Vector2<float>& contactNormal, const float& halfIntersectDistance)
	{
		const float bounce{ 1 + rigidbody->GetPhysicMaterial()->GetBounciness() };

		// Position reflection
		// Xt+dt = X't+dt - (1+BounceCoef)*(n·X't+dt + d)*n
		// Xt+dt = X't+dt + (contactNormal * (1+BounceCoef + halfIntDist))
		Vector2<float> position = rigidbody->p_position + (contactNormal * (bounce * halfIntersectDistance));

		rigidbody->p_position = position;


		// Velocity reflection
		// Vt+dt = V't+dt - (1+BounceCoef)*(n·V't+dt)*n
		Vector2<float> velocity = rigidbody->p_velocity -
			(contactNormal * (bounce * Vector2<float>::Dot(contactNormal, rigidbody->p_velocity)));

		rigidbody->p_velocity = velocity;
	}



}