#include "TextureState.h"

TextureState::TextureState()
	: 
	texture(NULL),
	sourceRect(NULL),
	destinationRect(),
	rotationInDegrees(0.0f),
	center(NULL),
	flip(SDL_FLIP_NONE)
{
}
