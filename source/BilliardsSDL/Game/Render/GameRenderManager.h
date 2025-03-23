#pragma once
#include <SDL_image.h>

#include "../../Shared/Types/Color/Color.h"
#include "../../Shared/Types/Vector2/Vector2.h"
#include "../../Application/Systems/Render/RenderSystem.h"


class GameRenderManager
{
public:
	GameRenderManager();
	GameRenderManager(RenderSystem* renderSystem);
	~GameRenderManager();

	const Vector2<int> GetWindowSize() const;
	void SetBackgroundColor(const Color& color) const;
	void DrawLine(const Color& color, const Vector2<int>& start, const Vector2<int>& end) const;


private:
	void SetDrawColor(const Color& color) const;


private:
	RenderSystem* m_renderSystem;

};