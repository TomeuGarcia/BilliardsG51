#include "ImageResourceData.h"


ImageResourceData::ImageResourceData(const std::string& sourcePath, const Vector2<int>& sourcePosition, const Vector2<int>& sourceSize)
	: p_sourcePath(sourcePath), p_sourceRect{ sourcePosition.x, sourcePosition.y, sourceSize.x, sourceSize.y }
{
}

ImageResourceData::~ImageResourceData()
{
}
