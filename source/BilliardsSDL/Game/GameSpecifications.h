#pragma once
#include <filesystem>
#include "../Shared/Types/Vector2/Vector2.h"
#include "Scenes/SceneName.h"

struct GameSpecifications
{
public:
	GameSpecifications(const std::string& pathToResourceFiles, const std::string& pathToResourceAssets) :
		p_pathToResourceFiles(pathToResourceFiles),
		p_pathToResourceImages(pathToResourceAssets + "Images/"),
		p_pathToResourceFonts(pathToResourceAssets + "Fonts/"),
		p_pathToResourceAudios(pathToResourceAssets + "Audios/"),
		p_startingScene(SceneName::MainMenu),
		p_worldWidthInWindow(14.4f)
	{
	}

public:
	std::string p_pathToResourceFiles;
	std::string p_pathToResourceImages;
	std::string p_pathToResourceFonts;
	std::string p_pathToResourceAudios;
	SceneName p_startingScene;
	float p_worldWidthInWindow;
};