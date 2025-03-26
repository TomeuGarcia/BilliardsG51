#pragma once
#include "../Vector2/Vector2.h"
#include "../Rect/Rect.h"

struct Circle
{
public:
	Circle(const Vector2<float>& position, const float& radius)
		: p_position(position)
	{
		SetRadius(radius);
	}

	void SetRadius(const float& radius)
	{
		m_radius = radius > 0 ? radius : 0;
	}
	float GetRadius() const
	{
		return m_radius;
	}

	Rect<float> MakeAARect() const
	{
		return Rect<float>(p_position, m_radius * 2, m_radius * 2);
	}


public:
	Vector2<float> p_position;
private:
	float m_radius;

};
