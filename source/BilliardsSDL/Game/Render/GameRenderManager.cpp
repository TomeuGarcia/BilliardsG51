#include "GameRenderManager.h"

GameRenderManager::GameRenderManager()
	: m_renderSystem(nullptr)
{
}

GameRenderManager::GameRenderManager(RenderSystem* renderSystem)
	: m_renderSystem(renderSystem)
{
}

GameRenderManager::~GameRenderManager()
{
}

const Vector2<int> GameRenderManager::GetWindowSize() const
{
	return m_renderSystem->GetWindowSize();
}

void GameRenderManager::SetBackgroundColor(const Color& color) const
{
	m_renderSystem->SetBackgroundColor(color);
}

void GameRenderManager::DrawLine(const Color& color, const Vector2<int>& start, const Vector2<int>& end) const
{
	SetDrawColor(color);
	SDL_RenderDrawLine(m_renderSystem->GetRenderer(), start.x, start.y, end.x, end.y);
}

void GameRenderManager::SetDrawColor(const Color& color) const
{
	SDL_SetRenderDrawColor(m_renderSystem->GetRenderer(), color.r, color.g, color.b, color.a);
}
