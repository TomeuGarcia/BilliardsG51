#include "RenderSystem.h"

RenderSystem::RenderSystem()
	: m_window(nullptr), m_renderer(nullptr), m_backgroundColor{ Colors::Black }, m_windowSize(0,0),
	m_debugTexture(nullptr)
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

	m_debugTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, m_windowSize.x, m_windowSize.y);	
	SDL_SetTextureBlendMode(m_debugTexture, SDL_BLENDMODE_BLEND);

	TTF_Init();
}

void RenderSystem::Cleanup()
{
	TTF_Quit();
	SDL_DestroyTexture(m_debugTexture);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
}


void RenderSystem::ClearRenderer()
{
	StartDrawingToDebug();
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
	SDL_RenderClear(m_renderer);	


	StopDrawingToDebug();
	SDL_SetRenderDrawColor(m_renderer, m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, m_backgroundColor.a);
	SDL_RenderClear(m_renderer);
}

void RenderSystem::DrawRenderer()
{
	SDL_RenderCopyEx(m_renderer, m_debugTexture, NULL, NULL, 0, NULL, SDL_FLIP_NONE); // Draw debug on top
	SDL_RenderPresent(m_renderer);
}



void RenderSystem::StartDrawingToDebug()
{
	SDL_SetRenderTarget(m_renderer, m_debugTexture);
}

void RenderSystem::StopDrawingToDebug()
{
	SDL_SetRenderTarget(m_renderer, NULL);
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
