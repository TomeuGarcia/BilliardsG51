#pragma once

#include <SDL_image.h>
#include "../../GameObjects/Transform.h"



class Renderer
{
public:
	Renderer(Transform* transform, const Vector2<int>& size);
	virtual ~Renderer();

	void Render(SDL_Renderer* outputRenderer);

private:
	const SDL_Rect ComputeDestination();


public:
	Vector2<int> p_size;
	float p_rotationInDegrees;
	SDL_RendererFlip p_flip;

protected:
	SDL_Rect r_sourceRect;
	SDL_Texture* r_texture;

private:
	Transform* m_transform;
};
