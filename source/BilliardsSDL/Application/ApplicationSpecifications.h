#pragma once
#include "../Game/GameSpecifications.h"

struct ApplicationSpecifications
{
public:
	ApplicationSpecifications()	: 
		p_windowSize(960, 540), 
		p_gameSpecifications()
	{
	}

public:
	Vector2<int> p_windowSize;
	GameSpecifications p_gameSpecifications;
};