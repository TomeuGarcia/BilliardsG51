#pragma once
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>

#include "../../Shared/Types/Rect/Rect.h"
#include "../../Shared/Types/Color/Color.h"
#include "../../Application/Systems/Render/RenderSystem.h"
#include "Renderers/Image/ImageResourceData.h"
#include "Renderers/Text/TextResourceData.h"
#include "Renderers/Renderer.h"

#include "OutputRenderer.h"
#include "Camera/CameraSystem.h"
#include "IGameSpacesComputer.h"


class GameRenderManager
{
public:
	GameRenderManager(RenderSystem* renderSystem, IGameSpacesComputer* gameSpacesComputer);
	~GameRenderManager();

public:
	static GameRenderManager* GetInstance();

public:
	ICameraFunctionalities* GetCameraFunctionalities();

public:
	const Vector2<int> GetWindowSize() const;
	void SetBackgroundColor(const Color& color) const;
	Color GetBackgroundColor() const;

	void DrawGizmoLine(const Color& color, const Line<float>& line);
	void DrawGizmoLine(const Color& color, const Vector2<float>& start, const Vector2<float>& end);
	void DrawGizmoLines(const Color& color, const std::vector<Vector2<float>>& points);
	void DrawGizmoRect(const Color& color, const Rect<float>& rect);

public:
	SDL_Texture* LoadImageTexture(const ImageResourceData& imageResourceData) const;
	SDL_Texture* LoadTextTexture(const TextResourceData& textResourceData,
								 const std::string& text, const int pointSize, const Color& color,
								 Vector2<int>& outTextSize) const;

public:
	void AddToRenderQueue(const std::shared_ptr<Renderer>& renderer);
	void ClearRenderQueue();
	void UpdateRendererQueue();
	void UpdateState(const float& deltaTime);
	void DrawRendererQueue();



private:
	RenderSystem* m_renderSystem;
	std::vector<std::shared_ptr<Renderer>> m_renderersQueue;

	CameraSystem m_cameraSystem;
	OutputRenderer m_outputRenderer;

private:
	static GameRenderManager* s_instance;
};