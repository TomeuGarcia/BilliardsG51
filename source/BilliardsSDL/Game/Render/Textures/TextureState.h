#pragma once
#include <SDL_image.h>


struct TextureState
{
public:
	TextureState();

public:
	SDL_Texture* texture;
	SDL_Rect* sourceRect;
	SDL_Rect destinationRect;
	float rotationInDegrees;
	SDL_Point* center;
	SDL_RendererFlip flip;
};