#pragma once
#include <SDL.h>
//#include <SDL_mixer.h>
//#include <SDL_ttf.h>

#include "Systems/Render/RenderSystem.h"


class BilliardsApplication
{
public:
	BilliardsApplication();
	~BilliardsApplication();
	void Run();

private:
	void InitSDL();
	void InitSystems();

	void CleanupSystems();
	void CleanupSDL();

private:
	void GameLoop();


private:
	ApplicationSpecifications _specifications;
	RenderSystem _renderSystem;
};

