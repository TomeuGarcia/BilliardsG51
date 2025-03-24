#pragma once
#include <string>
#include "../Shared/Types/Vector2/Vector2.h"
#include "Scenes/SceneName.h"

struct GameSpecifications
{
public:
	GameSpecifications(const std::string& pathToResourceAssets) :
		p_pathToResourceImages(pathToResourceAssets + "Images/"),
		p_pathToResourceFonts(pathToResourceAssets + "Fonts/"),
		p_pathToResourceAudios(pathToResourceAssets + "Audios/"),
		p_startingScene(SceneName::MainMenu)
	{
	}

public:
	std::string p_pathToResourceImages;
	std::string p_pathToResourceFonts;
	std::string p_pathToResourceAudios;
	SceneName p_startingScene;
};