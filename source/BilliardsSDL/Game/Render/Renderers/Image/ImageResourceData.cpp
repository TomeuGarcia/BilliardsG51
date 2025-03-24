#include "ImageResourceData.h"


ImageResourceData::ImageResourceData(const std::string& sourcePath, 
									 const Vector2<int>& sourcePosition, const Vector2<int>& sourceSize,
									 const bool& alphaTransparency)
	: p_sourcePath(sourcePath), 
	p_sourceRect{ sourcePosition.x, sourcePosition.y, sourceSize.x, sourceSize.y },
	p_alphaTransparency(alphaTransparency)
{
}

ImageResourceData::~ImageResourceData()
{
}
