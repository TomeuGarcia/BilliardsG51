#pragma once
#include "../Vector2/Vector2.h"


struct Line
{
public:
	Line(const Vector2<float>& origin, const Vector2<float>& end)
		: m_origin(origin), m_end(end), m_direction((end - origin).Normalized())
	{
	}
	Line(const Vector2<float>& origin, const Vector2<float>& direction, const float& distance)
		: m_origin(origin), m_end(origin + (direction * distance)), m_direction(direction)
	{
	}


	Vector2<float> GetOrigin() const
	{
		return m_origin;
	}
	
	Vector2<float> GetEnd() const
	{
		return m_end;
	}

	Vector2<float> GetDirection() const
	{
		return m_direction;
	}

	Vector2<float> GetPoint(const float& lambda) const
	{
		return m_origin + (m_direction * lambda);
	}


private:
	Vector2<float> m_origin;
	Vector2<float> m_end;
	Vector2<float> m_direction;
};