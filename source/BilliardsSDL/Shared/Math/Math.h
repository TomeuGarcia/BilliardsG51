#pragma once
#include <iostream>
#include <math.h>
#include <limits>
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

	float ComputeLineToPointDistance(const Line<float>& line, const Vector2<float>& point);
	bool ComputeLineToCircleDistance(const Line<float>& line, const Circle& circle, Vector2<float>& outPointInLine, float& outDistanceToCircleCenter);

	bool AreLineAndCircleIntersecting(const Line<float>& line, const Circle& circle); //
	bool AreRectAndCircleIntersecting(const Rect<float>& rect, const Circle& circle); //


	Line<float> GetClosestRectEdgeLineToPoint(const Vector2<float>& point, const Rect<float>& rect, float& outDistanceToClosestEdge);

	bool GetCollisiontRectEdgeLineWithCircle(const Circle& circle, const Rect<float>& rect,
		Line<float>& outCollisionLineEdge, Vector2<float>& collisionPointOnEdge, float& outDistanceEdgeToCircleCenter);


	bool AreLinesIntersecting(const Line<float>& lineA, const Line<float>& lineB);
	bool IsLineIntersectingAARect(const Line<float>& line, const Rect<float>& rect);

}