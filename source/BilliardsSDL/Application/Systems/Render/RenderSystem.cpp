#include "RenderSystem.h"

RenderSystem::RenderSystem()
	: m_window(nullptr), m_renderer(nullptr), m_backgroundColor{ Colors::Black }, m_windowSize(0,0)
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::Init(const Vector2<int>& windowSize)
{
	m_windowSize = windowSize;
	int initResult = SDL_CreateWindowAndRenderer(m_windowSize.x, m_windowSize.y,
												 SDL_WINDOW_SHOWN,
												 &m_window, &m_renderer);
	bool initialized = initResult >= 0;
	if (!initialized)
	{
		std::cout << SDL_GetError() << std::endl;
	}
}

void RenderSystem::Cleanup()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
}


void RenderSystem::ClearRenderer()
{
	SDL_SetRenderDrawColor(m_renderer, m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, m_backgroundColor.a);
	SDL_RenderClear(m_renderer);
}

void RenderSystem::DrawRenderer()
{
	SDL_RenderPresent(m_renderer);
}

SDL_Renderer* RenderSystem::GetRenderer() const
{
	return m_renderer;
}

const Vector2<int> RenderSystem::GetWindowSize() const
{
	return m_windowSize;
}

void RenderSystem::SetBackgroundColor(const Color& color)
{
	m_backgroundColor = color;
}
