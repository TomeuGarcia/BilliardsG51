#include "GameRenderManager.h"

GameRenderManager* GameRenderManager::s_instance = nullptr;

GameRenderManager::GameRenderManager(RenderSystem* renderSystem)
	: m_renderSystem(renderSystem), m_renderersQueue()
{
	m_renderersQueue.reserve(20);
	s_instance = this;
}

GameRenderManager::~GameRenderManager()
{
	s_instance = nullptr;
}



GameRenderManager* GameRenderManager::GetInstance()
{
	return s_instance;
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



SDL_Texture* GameRenderManager::LoadImageTexture(const ImageResourceData& imageResourceData) const
{
	SDL_Surface* surface = IMG_Load(imageResourceData.p_sourcePath.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderSystem->GetRenderer(), surface);
	SDL_FreeSurface(surface);

	return texture;
}



void GameRenderManager::AddToRenderQueue(const std::shared_ptr<Renderer> renderer)
{
	m_renderersQueue.emplace_back(renderer);
}

void GameRenderManager::ClearRenderQueue()
{
	m_renderersQueue.clear();
}

void GameRenderManager::DrawRendererQueue()
{
	for (auto it = m_renderersQueue.begin(); it != m_renderersQueue.end(); ++it)
	{
		(*it)->Render(m_renderSystem->GetRenderer());
	}
}




void GameRenderManager::SetDrawColor(const Color& color) const
{
	SDL_SetRenderDrawColor(m_renderSystem->GetRenderer(), color.r, color.g, color.b, color.a);
}
