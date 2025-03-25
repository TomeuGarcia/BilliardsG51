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


class GameRenderManager
{
public:
	GameRenderManager(RenderSystem* renderSystem);
	~GameRenderManager();

public:
	static GameRenderManager* GetInstance();

public:
	const Vector2<int> GetWindowSize() const;
	void SetBackgroundColor(const Color& color) const;
	void DrawDebugLine(const Color& color, const Vector2<int>& start, const Vector2<int>& end) const;
	void DrawDebugRect(const Color& color, const Rect<int>& rect) const;

public:
	SDL_Texture* LoadImageTexture(const ImageResourceData& imageResourceData) const;
	SDL_Texture* LoadTextTexture(const TextResourceData& textResourceData,
								 const std::string& text, const int pointSize, const Color& color,
								 Vector2<int>& outTextSize) const;

public:
	void AddToRenderQueue(const std::shared_ptr<Renderer> renderer);
	void ClearRenderQueue();
	void DrawRendererQueue();


private:
	void SetDrawColor(const Color& color) const;



private:
	RenderSystem* m_renderSystem;
	std::vector<std::shared_ptr<Renderer>> m_renderersQueue;

private:
	static GameRenderManager* s_instance;
};