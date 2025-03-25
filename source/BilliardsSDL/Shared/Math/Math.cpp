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



	bool IsPointInsideRect(const Rect<float>& rect, const Vector2<float>& vector)
	{
		return vector.x < (rect.x + rect.width)
			&& vector.x > rect.x
			&& vector.y < (rect.y + rect.height)
			&& vector.y > rect.y;
	}

	bool AreAARectsIntersecting(const Rect<float>& rectA, const Rect<float>& rectB)
	{
		return rectA.x + rectA.width > rectB.x
			&& rectA.x < rectB.x + rectB.width
			&& rectA.y + rectA.height > rectB.y
			&& rectA.y < rectB.y + rectB.height;
	}



	bool IsPointInsideCircle(const Vector2<float>& point, const Circle& circle)
	{
		return Vector2<float>::Distance(point, circle.p_position) < circle.GetRadius();
	}

	bool AreCirclesIntersecting(const Circle& circleA, const Circle& circleB)
	{
		return Vector2<float>::Distance(circleA.p_position, circleB.p_position) < (circleA.GetRadius() + circleB.GetRadius());
	}

	bool AreLineAndCircleIntersecting(const Line& line, const Circle& circle)
	{
		float t = Vector2<float>::Dot(circle.p_position - line.GetOrigin(), line.GetDirection());
		Vector2<float> p = line.GetOrigin() + (line.GetDirection() * t);
		float y = Vector2<float>::Distance(circle.p_position, p);

		return y < circle.GetRadius();
	}

	bool AreRectAndCircleIntersecting(const Rect<float>& rect, const Circle& circle)
	{
		return IsPointInsideRect(rect, circle.p_position) ||
			AreLineAndCircleIntersecting(rect.MakeLeftEdgeLine(), circle) ||
			AreLineAndCircleIntersecting(rect.MakeRightEdgeLine(), circle) ||
			AreLineAndCircleIntersecting(rect.MakeBottomEdgeLine(), circle) ||
			AreLineAndCircleIntersecting(rect.MakeTopEdgeLine(), circle);
	}
}