#pragma once
#include "ImageResourceData.h"
#include "../Renderer.h"
#include "../../GameRenderManager.h"


class Image : public Renderer
{
public:
	Image(GameObject* gameObject, const Vector2<float>& size);
	virtual ~Image();

	void Init(const GameRenderManager& renderManager, const ImageResourceData& resourceData);

protected:
	virtual SDL_Rect* GetSourceRect() override;


private:
	SDL_Rect m_sourceRect;
};
