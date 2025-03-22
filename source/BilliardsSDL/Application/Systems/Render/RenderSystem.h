#pragma once
#include <SDL_image.h>
#include <iostream>
#include "../../ApplicationSpecifications.h"

class RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();

	void Init(const ApplicationSpecifications& specifications);
	void Cleanup();

public:
	void ClearRenderer();
	void DrawRenderer();


private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;

};