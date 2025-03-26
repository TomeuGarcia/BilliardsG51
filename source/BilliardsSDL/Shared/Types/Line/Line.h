#pragma once
#include "../Vector2/Vector2.h"

template <typename T>
struct Line
{
public:
	Line()
		:m_origin(), m_end(), m_direction(), m_totalDistance(0)
	{}
	Line(const Vector2<T>& origin, const Vector2<T>& end)
		: m_origin(origin), m_end(end), m_direction((end - origin).Normalized()), m_totalDistance((end-origin).Length())
	{
	}
	Line(const Vector2<T>& origin, const Vector2<T>& direction, const T& distance)
		: m_origin(origin), m_end(origin + (direction * distance)), m_direction(direction), m_totalDistance(distance)
	{
	}


	Vector2<T> GetOrigin() const
	{
		return m_origin;
	}
	
	Vector2<T> GetEnd() const
	{
		return m_end;
	}

	Vector2<T> GetDirection() const
	{
		return m_direction;
	}

	T GetTotalDistance() const
	{
		return m_totalDistance;
	}

	Vector2<T> GetPoint(const T& lambda) const
	{
		return m_origin + (m_direction * lambda);
	}
	
	Vector2<T> GetPointAtRatio(const T& t) const
	{
		return Vector2<T>::Lerp(m_origin, m_end, t);
	}


private:
	Vector2<T> m_origin;
	Vector2<T> m_end;
	Vector2<T> m_direction;
	T m_totalDistance;
};