#include "OutputRenderer.h"






OutputRenderer::OutputRenderer(SDL_Renderer* renderer, CameraTransformations* cameraTransformations, IGameSpacesComputer* gameSpacesComputer)
	: m_renderer(renderer),
	m_cameraTransformations(cameraTransformations),
	m_gameSpacesComputer(gameSpacesComputer)
{
}




void OutputRenderer::DrawLine(const Color& color, const Vector2<float>& start, const Vector2<float>& end)
{
	SetDrawColor(color);
	Vector2<int> realStart = TransformToWindow(start);
	Vector2<int> realEnd = TransformToWindow(end);
	SDL_RenderDrawLine(m_renderer, realStart.x, realStart.y, realEnd.x, realEnd.y);
}


void OutputRenderer::DrawLines(const Color& color, const std::vector<Vector2<float>>& points)
{
	SetDrawColor(color);

	std::vector<SDL_Point> windowPoints(points.size());
	for (size_t i = 0; i < points.size(); ++i)
	{
		Vector2<int> windowPoint = TransformToWindow(points[i]);
		windowPoints[i] = SDL_Point{ windowPoint.x, windowPoint.y };
	}

	SDL_RenderDrawLines(m_renderer, &*windowPoints.begin(), windowPoints.size());
}

void OutputRenderer::DrawRect(const Color& color, const Rect<float>& rect)
{
	SetDrawColor(color);
	SDL_Rect windowRect = TransformToWindow(rect).ToSDLRect();
	SDL_RenderDrawRect(m_renderer, &windowRect);
}




void OutputRenderer::DrawTexture(TextureState& textureState)
{
	SDL_Rect destinationRect = textureState.destinationRect;

	SDL_RenderCopyEx(m_renderer, textureState.texture,
		textureState.sourceRect, &destinationRect,
		textureState.rotationInDegrees, textureState.center, textureState.flip);
}




void OutputRenderer::SetDrawColor(const Color& color) const
{
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
}

Vector2<int> OutputRenderer::TransformToWindow(const Vector2<float>& point)
{
	const Vector2<float> cameraRelativePoint = m_cameraTransformations->ApplyToWorldPosition(point);
	const Vector2<int> windowPoint = m_gameSpacesComputer->WorldToWindowPosition(cameraRelativePoint);

	return windowPoint;
}

Rect<int> OutputRenderer::TransformToWindow(const Rect<float>& rect)
{
	Rect<float> cameraRelativeRect{
		m_cameraTransformations->ApplyToWorldPosition(rect.GetCenterPosition()),
		rect.GetSize()
	};
	const Rect<int> windowRect = m_gameSpacesComputer->WorldToWindowRect(cameraRelativeRect);

	return windowRect;
}

