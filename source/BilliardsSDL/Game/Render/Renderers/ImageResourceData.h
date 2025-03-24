#pragma once
#include <string>
#include <SDL_image.h>

#include "../../../Shared/Types/Vector2/Vector2.h"

struct ImageResourceData
{
public:
	ImageResourceData(std::string&& sourcePath, Vector2<int> sourcePosition, Vector2<int> sourceSize);
	~ImageResourceData();

public:
	std::string p_sourcePath;
	SDL_Rect p_sourceRect;
};