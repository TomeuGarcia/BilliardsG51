#include "Image.h"


Image::Image(GameObject* gameObject, const Vector2<int>& size)
	: Renderer(gameObject, size)
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
