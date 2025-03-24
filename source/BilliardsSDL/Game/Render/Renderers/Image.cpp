#include "Image.h"


Image::Image(Transform* transform, const Vector2<int>& size)
	: Renderer(transform, size)
{
}

Image::~Image()
{
}

void Image::Init(const GameRenderManager& renderManager, const ImageResourceData& resourceData)
{
	r_sourceRect = resourceData.p_sourceRect;
	r_texture = renderManager.LoadImageTexture(resourceData);
}
