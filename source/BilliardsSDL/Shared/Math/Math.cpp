#include "Math.h"

namespace Math
{
	float Sqrt(const float& value)
	{
		return sqrtf(value);
	}

	float Min(const float& a, const float& b)
	{
		return a < b ? a : b;
	}

	float Max(const float& a, const float& b)
	{
		return a > b ? a : b;
	}

	float Clamp(const float& value, const float& min, const float& max)
	{
		return value > max ? max
			: (value < min ? min : value);
	}

	float Clamp01(const float& value)
	{
		return Clamp(value, 0.0f, 1.0f);
	}



	bool IsPointInsideRect(const Rect<float>& rect, const Vector2<float>& point)
	{
		return point.x < (rect.GetBottomLeftX() + rect.GetWidth())
			&& point.x > rect.GetBottomLeftX()
			&& point.y < (rect.GetBottomLeftY() + rect.GetHeight())
			&& point.y > rect.GetBottomLeftY();
	}

	bool AreAARectsIntersecting(const Rect<float>& rectA, const Rect<float>& rectB)
	{
		return rectA.GetBottomLeftX() + rectA.GetWidth() > rectB.GetBottomLeftX()
			&& rectA.GetBottomLeftX() < rectB.GetBottomLeftX() + rectB.GetWidth()
			&& rectA.GetBottomLeftY() + rectA.GetHeight() > rectB.GetBottomLeftY()
			&& rectA.GetBottomLeftY() < rectB.GetBottomLeftY() + rectB.GetHeight();
	}



	bool IsPointInsideCircle(const Vector2<float>& point, const Circle& circle)
	{
		return Vector2<float>::Distance(point, circle.p_position) < circle.GetRadius();
	}

	bool AreCirclesIntersecting(const Circle& circleA, const Circle& circleB)
	{
		return Vector2<float>::Distance(circleA.p_position, circleB.p_position) < (circleA.GetRadius() + circleB.GetRadius());
	}


	float ComputeLineToPointDistance(const Line<float>& line, const Vector2<float>& point)
	{
		float distanceLineOriginToCircleProjectedOnLine = Vector2<float>::Dot(point - line.GetOrigin(), line.GetDirection());
		Vector2<float> linePointPerpendicularToCircle = line.GetOrigin() + (line.GetDirection() * distanceLineOriginToCircleProjectedOnLine);
		float distanceLineToCircle = Vector2<float>::Distance(point, linePointPerpendicularToCircle);

		return distanceLineToCircle;
	}



	bool ComputeLineToCircleDistance(const Line<float>& line, const Circle& circle, Vector2<float>& outPointInLine, float& outDistanceToPoint)
	{
		// First check if point projects on line segment
		// - if true, compute and return

		Vector2<float> lineOriginToCirclePosition = circle.p_position - line.GetOrigin();
		float distanceLineOriginToCircleProjectedOnLine = Vector2<float>::Dot(lineOriginToCirclePosition, line.GetDirection());
		bool projectsOnLine = distanceLineOriginToCircleProjectedOnLine > 0 &&
							  distanceLineOriginToCircleProjectedOnLine < line.GetTotalDistance();

		if (projectsOnLine)
		{
			outPointInLine = line.GetOrigin() + (line.GetDirection() * distanceLineOriginToCircleProjectedOnLine);
			outDistanceToPoint = Vector2<float>::Distance(circle.p_position, outPointInLine);
			
			return true;
		}



		// Second check if line end points are inside circle
		// - if true, compute closest and return
		const float circleToLineOriginDistance = lineOriginToCirclePosition.Length();
		const bool circlePenetratingOrigin = circleToLineOriginDistance < circle.GetRadius();
		if (circlePenetratingOrigin)
		{
			outPointInLine = line.GetOrigin();
			outDistanceToPoint = circleToLineOriginDistance;
			return true;
		}		

		const float circleToLineEndDistance = (circle.p_position - line.GetEnd()).Length();
		const bool circlePenetratingEnd = circleToLineEndDistance < circle.GetRadius();
		if (circlePenetratingEnd)
		{
			outPointInLine = line.GetEnd();
			outDistanceToPoint = circleToLineEndDistance;
			return true;
		}


		return false;
	}





	bool AreLineAndCircleIntersecting(const Line<float>& line, const Circle& circle)
	{
		return ComputeLineToPointDistance(line, circle.p_position) < circle.GetRadius();
	}

	bool AreRectAndCircleIntersecting(const Rect<float>& rect, const Circle& circle)
	{
		return IsPointInsideRect(rect, circle.p_position) ||
			AreLineAndCircleIntersecting(rect.MakeLeftEdgeLine(), circle) ||
			AreLineAndCircleIntersecting(rect.MakeRightEdgeLine(), circle) ||
			AreLineAndCircleIntersecting(rect.MakeBottomEdgeLine(), circle) ||
			AreLineAndCircleIntersecting(rect.MakeTopEdgeLine(), circle);
	}



	Line<float> GetClosestRectEdgeLineToPoint(const Vector2<float>& point, const Rect<float>& rect, float& outDistanceToClosestEdge)
	{
		Line<float> leftEdge = rect.MakeLeftEdgeLine();
		const float leftDistance = ComputeLineToPointDistance(leftEdge, point);

		Line<float> rightEdge = rect.MakeRightEdgeLine();
		const float rightDistance = ComputeLineToPointDistance(rightEdge, point);

		Line<float> bottomEdge = rect.MakeBottomEdgeLine();
		const float bottomDistance = ComputeLineToPointDistance(bottomEdge, point);

		Line<float> topEdge = rect.MakeTopEdgeLine();
		const float topDistance = ComputeLineToPointDistance(topEdge, point);


		Line<float>& closestEdge = leftEdge;
		outDistanceToClosestEdge = leftDistance;
		if (rightDistance < outDistanceToClosestEdge)
		{
			closestEdge = rightEdge;
			outDistanceToClosestEdge = rightDistance;
		}
		if (bottomDistance < outDistanceToClosestEdge)
		{
			closestEdge = bottomEdge;
			outDistanceToClosestEdge = bottomDistance;
		}
		if (topDistance < outDistanceToClosestEdge)
		{
			closestEdge = topEdge;
			outDistanceToClosestEdge = topDistance;
		}


		return closestEdge;
	}



	bool GetCollisiontRectEdgeLineWithCircle(const Circle& circle, const Rect<float>& rect, 
		Line<float>& outCollisionLineEdge, Vector2<float>& collisionPointOnEdge, float& outDistanceToClosestEdge)
	{
		float leftDistance;
		Vector2<float> leftCollisionPoint;
		Line<float> leftEdge = rect.MakeLeftEdgeLine();
		const bool leftCollision = ComputeLineToCircleDistance(leftEdge, circle, leftCollisionPoint, leftDistance);


		float rightDistance;
		Vector2<float> rightCollisionPoint;
		Line<float> rightEdge = rect.MakeRightEdgeLine();
		const bool rightCollision = ComputeLineToCircleDistance(rightEdge, circle, rightCollisionPoint, rightDistance);


		float bottomDistance;
		Vector2<float> bottomCollisionPoint;
		Line<float> bottomEdge = rect.MakeBottomEdgeLine();
		const bool bottomCollision = ComputeLineToCircleDistance(bottomEdge, circle, bottomCollisionPoint, bottomDistance);


		float topDistance;
		Vector2<float> topCollisionPoint;
		Line<float> topEdge = rect.MakeTopEdgeLine();
		const bool topCollision = ComputeLineToCircleDistance(topEdge, circle, topCollisionPoint, topDistance);




		Line<float>& closestEdge = leftEdge;
		collisionPointOnEdge = leftCollisionPoint;
		outDistanceToClosestEdge = leftDistance;
		bool collided = leftCollision;


		if (rightCollision && rightDistance < outDistanceToClosestEdge)
		{
			closestEdge = rightEdge;
			collisionPointOnEdge = rightCollisionPoint;
			outDistanceToClosestEdge = rightDistance;
			collided = true;
		}
		if (bottomCollision && bottomDistance < outDistanceToClosestEdge)
		{
			closestEdge = bottomEdge;
			collisionPointOnEdge = bottomCollisionPoint;
			outDistanceToClosestEdge = bottomDistance;
			collided = true;
		}
		if (topCollision && topDistance < outDistanceToClosestEdge)
		{
			closestEdge = topEdge;
			collisionPointOnEdge = topCollisionPoint;
			outDistanceToClosestEdge = topDistance;
			collided = true;
		}


		return collided;
	}
}