#pragma once
#include <SDL_image.h>
#include "../../GameObjects/GameObject.h"
#include "../../../Shared/Types/Color/Color.h"
#include "../../../Shared/Math/Math.h"

#include "../IOutputRendererVisitor.h"
#include "../Camera/CameraTransformations.h"



class Renderer
{
public:
	Renderer(GameObject* gameObject, const Vector2<float>& worldSize);
	virtual ~Renderer();

	void Update(CameraTransformations* cameraTransformations);
	void Render(IOutputRendererVisitor* outputRenderer);

	void SetColorTint(const Color& color);
	Color GetColorTint() const;

	Rect<int> GetDestinationRect() const;
	bool IsActive() const;

	GameObject* GetGameObject() const;
	Transform* GetTransform() const;

	void SetRotation(const float& rotationInDegrees);
	float GetRotation() const;


protected:
	void InitTexture(SDL_Texture* texture);

	virtual SDL_Rect* GetSourceRect() = 0;

private:
	const SDL_Rect UpdateDestination(CameraTransformations* cameraTransformations);


public:
	Vector2<float> p_scale;

protected:
	Vector2<float> r_worldSize;

private:
	GameObject* m_gameObject;
	Color m_colorTint;
	Rect<int> m_destinationRect;

	TextureState m_textureState;
};
