#pragma once
#include <iostream>
#include <cmath>
#include <math.h>
#include <limits>
#include "../Types/Vector2/Vector2.h"
#include "../Types/Rect/Rect.h"
#include "../Types/Circle/Circle.h"
#include "../Types/Line/Line.h"

namespace Math
{
#define PI 3.14159265f

	float Modulo(float value, float divisor);
	float Pow(const float& base, const float& exponent);

	float Abs(const float& value);

	float Sqrt(const float& value);

	float Min(const float& a, const float& b);
	float Max(const float& a, const float& b);
	float Clamp(const float& value, const float& min, const float& max);	
	float Clamp01(const float& value);

	float Lerp(const float& a, const float& b, const float& t);

	float Rad2Deg(const float& radians);
	float Deg2Rad(const float& degrees);

	float Sin(const float& radians);
	float Cos(const float& radians);
	float Sin01(const float& radians);


	float Angle(const Vector2<float>& from, const Vector2<float>& to);


	Vector2<float> Rotate(const Vector2<float>& vector, const float& degrees);


	bool IsPointInsideRect(const Rect<float>& rect, const Vector2<float>& point);
	bool IsPointInsideRect(const Rect<int>& rect, const Vector2<int>& point);
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


	bool AreLinesIntersecting(const Line<float>& lineA, const Line<float>& lineB, Vector2<float>& outIntersectionPoint);

	bool ComputeLineToAARectDistance(const Line<float>& line, const Rect<float>& rect, Vector2<float>& outPointInLine, float& outDistanceToRectEdge);

}