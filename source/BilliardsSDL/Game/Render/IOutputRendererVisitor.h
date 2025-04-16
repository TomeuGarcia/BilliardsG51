#pragma once
#include "Textures/TextureState.h"


class IOutputRendererVisitor
{
public:
	virtual void DrawTexture(TextureState& textureState) = 0;
};