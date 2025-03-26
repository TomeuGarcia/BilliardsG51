#pragma once
#include "../Rigidbodies/Rigidbody2D.h"
#include "../../../Shared/Types/Circle/Circle.h"
#include "../../../Shared/Types/Rect/Rect.h"
#include "../../../Shared/Math/Math.h"


namespace CollisionHelper
{
	bool ComputeCirclesCollisionWithOutputData(const Circle& circleA, const Circle& circleB,
		Vector2<float>& outNormalForAB, float& outHalfIntersectionDistance);

	bool ComputeCircleAARectCollisionWithOutputData(const Circle& circleA, const Rect<float>& aaRectB,
		Vector2<float>& outNormalForA, Vector2<float>& outNormalForB, float& outHalfIntersectionDistance);

	bool ComputeAARectsCollisionWithOutputData(const Rect<float>& aaRectA, const Rect<float>& aaRectB,
		Vector2<float>& outNormalForAB, float& outHalfIntersectionDistance);


	void ApplyContactCollision(Rigidbody2D* rigidbody, const Vector2<float>& contactNormal, const float& halfIntersectDistance);


}