#pragma once
#include "../Game/GameSpecifications.h"

struct ApplicationSpecifications
{
public:
	ApplicationSpecifications()	: 
		p_windowSize(960, 540), 
		p_maxDeltaTime(1.0f / 30),
		p_gameSpecifications("../../resources/Files", "../../resources/Assets")
	{
	}

public:
	Vector2<int> p_windowSize;
	float p_maxDeltaTime;
	GameSpecifications p_gameSpecifications;
};