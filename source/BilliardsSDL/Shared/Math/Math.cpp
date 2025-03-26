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

	float ComputeLineToCircleDistance(const Line<float>& line, const Circle& circle)
	{
		return ComputeLineToPointDistance(line, circle.p_position) - circle.GetRadius();
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
}