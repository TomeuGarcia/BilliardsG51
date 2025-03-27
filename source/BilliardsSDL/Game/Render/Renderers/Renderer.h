#pragma once
#include <SDL_image.h>
#include "../../GameObjects/GameObject.h"
#include "../../../Shared/Types/Color/Color.h"
#include "../../../Shared/Math/Math.h"


class Renderer
{
public:
	Renderer(GameObject* gameObject, const Vector2<float>& worldSize);
	virtual ~Renderer();

	void Render(SDL_Renderer* outputRenderer);

	void SetColorTint(const Color& color);
	Color GetColorTint() const;

protected:
	virtual SDL_Rect* GetSourceRect() = 0;

private:
	const SDL_Rect ComputeDestination();


public:
	float p_rotationInDegrees;
	SDL_RendererFlip p_flip;
	Vector2<float> p_scale;

protected:
	Vector2<float> r_worldSize;
	SDL_Texture* r_texture;

private:
	GameObject* m_gameObject;
	Color m_colorTint;
};
