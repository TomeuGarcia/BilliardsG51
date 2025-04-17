#pragma once
#include <string>
#include <SDL_image.h>
#include "../../../../Shared/Types/Vector2/Vector2.h"


struct ImageResourceData
{
public:
	ImageResourceData(const std::string& sourcePath,
					  const Vector2<int>& sourcePosition, const Vector2<int>& sourceSize,
					  const bool& alphaTransparency,
					  const float& pixelsToUnits);

public:
	std::string p_sourcePath;
	SDL_Rect p_sourceRect;
	bool p_alphaTransparency;
	Vector2<float> p_defaultUnitsSize;
};