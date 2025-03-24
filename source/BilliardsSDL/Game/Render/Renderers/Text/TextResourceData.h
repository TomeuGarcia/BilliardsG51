#pragma once
#include <string>
#include <SDL_image.h>
#include "../../../../Shared/Types/Vector2/Vector2.h"
#include "../../../../Shared/Types/Color/Color.h"


struct TextResourceData
{
public:
	TextResourceData(const std::string& sourcePath);
	~TextResourceData();

public:
	std::string p_sourcePath;
};