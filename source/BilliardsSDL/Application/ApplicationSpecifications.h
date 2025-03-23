#pragma once
#include "../../../Shared/Types/Vector2/Vector2.h"

struct ApplicationSpecifications
{
public:
	ApplicationSpecifications(const Vector2<int>& windowSize)
		: p_windowSize(windowSize)
	{
	}

public:
	Vector2<int> p_windowSize;
};