#pragma once
#include "../Vector2/Vector2.h"

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


public:
	Vector2<float> p_position;
private:
	float m_radius;

};
