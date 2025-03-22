#include "RenderSystem.h"

RenderSystem::RenderSystem()
	: _window(nullptr), _renderer(nullptr)
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::Init(const ApplicationSpecifications& specifications)
{
	int initResult = SDL_CreateWindowAndRenderer(specifications.windowWidth, specifications.windowHeight,
												 SDL_WINDOW_SHOWN,
												 &_window, &_renderer);
	bool initialized = initResult >= 0;
	if (!initialized)
	{
		std::cout << SDL_GetError() << std::endl;
	}
}

void RenderSystem::Cleanup()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
}


void RenderSystem::ClearRenderer()
{
	SDL_RenderClear(_renderer);
}

void RenderSystem::DrawRenderer()
{
	SDL_RenderPresent(_renderer);
}
