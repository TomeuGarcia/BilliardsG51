#include "ImageResourceData.h"


ImageResourceData::ImageResourceData(std::string&& sourcePath, Vector2<int> sourcePosition, Vector2<int> sourceSize)
	: p_sourcePath(sourcePath), p_sourceRect{ sourcePosition.x, sourcePosition.y, sourceSize.x, sourceSize.y }
{
}

ImageResourceData::~ImageResourceData()
{
}
