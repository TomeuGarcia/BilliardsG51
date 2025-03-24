#include "Image.h"


Image::Image(GameObject* gameObject, const Vector2<int>& size)
	: Renderer(gameObject, size), 
	m_sourceRect()
{
}

Image::~Image()
{
}

void Image::Init(const GameRenderManager& renderManager, const ImageResourceData& resourceData)
{
	m_sourceRect = resourceData.p_sourceRect;
	r_texture = renderManager.LoadImageTexture(resourceData);
}

SDL_Rect* Image::GetSourceRect()
{
	return &m_sourceRect;
}
