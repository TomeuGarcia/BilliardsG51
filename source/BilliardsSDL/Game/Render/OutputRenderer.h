#pragma once
#include <vector>
#include <SDL_image.h>

#include "IOutputRendererVisitor.h"
#include "Textures/TextureState.h"

#include "../../Shared/Types/Color/Color.h"
#include "../../Shared/Types/Rect/Rect.h"

#include "Camera/CameraTransformations.h"
#include "IGameSpacesComputer.h"


class OutputRenderer : public IOutputRendererVisitor
{
public:
	OutputRenderer(SDL_Renderer* renderer, CameraTransformations* cameraTransformations, IGameSpacesComputer* gameSpacesComputer);


public:
	void DrawLine(const Color& color, const Vector2<float>& start, const Vector2<float>& end);
	void DrawLines(const Color& color, const std::vector<Vector2<float>>& points);
	void DrawRect(const Color& color, const Rect<float>& rect);


public:
	virtual void DrawTexture(TextureState& textureState) override;


private:
	void SetDrawColor(const Color& color) const;

	Vector2<int> TransformToWindow(const Vector2<float>& point);
	Rect<int> TransformToWindow(const Rect<float>& rect);


private:
	SDL_Renderer* m_renderer;
	CameraTransformations* m_cameraTransformations;
	IGameSpacesComputer* m_gameSpacesComputer;
};