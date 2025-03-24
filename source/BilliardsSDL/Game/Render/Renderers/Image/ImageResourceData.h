#pragma once
#include <string>
#include <SDL_image.h>
#include "../../../../Shared/Types/Vector2/Vector2.h"


struct ImageResourceData
{
public:
	ImageResourceData(const std::string& sourcePath, const Vector2<int>& sourcePosition, const Vector2<int>& sourceSize);
	~ImageResourceData();

public:
	std::string p_sourcePath;
	SDL_Rect p_sourceRect;
};