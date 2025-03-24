#pragma once
#include <string>
#include "../Shared/Types/Vector2/Vector2.h"
#include "Scenes/SceneName.h"

struct GameSpecifications
{
public:
	GameSpecifications() :
		p_pathToResources("../../resources/"),
		p_startingScene(SceneName::MainMenu)
	{
	}

public:
	std::string p_pathToResources;
	SceneName p_startingScene;
};