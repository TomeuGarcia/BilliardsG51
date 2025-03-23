#pragma once
#include <SDL_image.h>
#include <iostream>
#include "../../ApplicationSpecifications.h"
#include "../../../Shared/Types/Color/Color.h"
#include "../../../Shared/Types/Vector2/Vector2.h"

class RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();

	void Init(const Vector2<int>& windowSize);
	void Cleanup();

public:
	void ClearRenderer();
	void DrawRenderer();

	SDL_Renderer* GetRenderer() const;
	const Vector2<int> GetWindowSize() const;
	void SetBackgroundColor(const Color& color);


private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	Color m_backgroundColor;
	Vector2<int> m_windowSize;
};