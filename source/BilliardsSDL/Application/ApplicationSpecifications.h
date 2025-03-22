#pragma once

struct ApplicationSpecifications
{
public:
	ApplicationSpecifications(int startWindowWidth, int startWindowHeight)
		: windowWidth(startWindowWidth), windowHeight(startWindowHeight)
	{
	}

public:
	int windowWidth;
	int windowHeight;
};