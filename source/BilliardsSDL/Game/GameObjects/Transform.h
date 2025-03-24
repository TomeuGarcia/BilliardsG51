#pragma once
#include "../../Shared/Types/Vector2/Vector2.h"


class Transform
{
public:
	Transform(Vector2<int> position);

public:
	Vector2<int> p_position;
};