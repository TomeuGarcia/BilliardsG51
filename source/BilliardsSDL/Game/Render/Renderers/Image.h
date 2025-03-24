#pragma once
#include "Renderer.h"
#include "ImageResourceData.h"
#include "../GameRenderManager.h"


class Image : public Renderer
{
public:
	Image(Transform* transform, const Vector2<int>& size);
	virtual ~Image();

	void Init(const GameRenderManager& renderManager, const ImageResourceData& resourceData);


};
