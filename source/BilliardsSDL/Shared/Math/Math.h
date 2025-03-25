#pragma once
#include <math.h>
#include "../Types/Vector2/Vector2.h"
#include "../Types/Rect/Rect.h"
#include "../Types/Circle/Circle.h"
#include "../Types/Line/Line.h"

namespace Math
{
	float Sqrt(const float& value);

	float Min(const float& a, const float& b);
	float Max(const float& a, const float& b);
	float Clamp(const float& value, const float& min, const float& max);	
	float Clamp01(const float& value);



	bool IsPointInsideRect(const Rect<float>& rect, const Vector2<float>& vector);
	bool AreAARectsIntersecting(const Rect<float>& rectA, const Rect<float>& rectB);

	
	bool IsPointInsideCircle(const Vector2<float>& point, const Circle& circle);
	bool AreCirclesIntersecting(const Circle& circleA, const Circle& circleB);
	bool AreLineAndCircleIntersecting(const Line& line, const Circle& circle);
	bool AreRectAndCircleIntersecting(const Rect<float>& rect, const Circle& circle);
}