#pragma once
#include <filesystem>
#include "../Shared/Types/Vector2/Vector2.h"
#include "Scenes/SceneName.h"

struct GameSpecifications
{
public:
	GameSpecifications(const std::filesystem::path& pathToResourceFiles, const std::filesystem::path& pathToResourceAssets) :
		p_pathToResourceFiles(pathToResourceFiles),
		p_pathToResourceImages(pathToResourceAssets / "Images/"),
		p_pathToResourceFonts(pathToResourceAssets / "Fonts/"),
		p_pathToResourceAudios(pathToResourceAssets / "Audios/"),
		p_startingScene(SceneName::MainMenu),
		p_worldWidthInWindow(14.4f)
	{
	}

public:
	std::filesystem::path p_pathToResourceFiles;
	std::filesystem::path p_pathToResourceImages;
	std::filesystem::path p_pathToResourceFonts;
	std::filesystem::path p_pathToResourceAudios;
	SceneName p_startingScene;
	float p_worldWidthInWindow;
};