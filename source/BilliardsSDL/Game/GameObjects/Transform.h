#pragma once
#include "../../Shared/Types/Vector2/Vector2.h"
#include "../Systems/GameSpacesComputer.h"

class Transform
{
public:
	Transform(Vector2<float> worldPosition);

public:
	Vector2<float> p_worldPosition;
};