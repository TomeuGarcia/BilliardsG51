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

Color GameRenderManager::GetBackgroundColor() const
{
	return m_renderSystem->GetBackgroundColor();
}



void GameRenderManager::DrawDebugLine(const Color& color, const Vector2<int>& start, const Vector2<int>& end) const
{
	m_renderSystem->StartDrawingToDebug();
	SetDrawColor(color);
	SDL_RenderDrawLine(m_renderSystem->GetRenderer(), start.x, start.y, end.x, end.y);
	m_renderSystem->StopDrawingToDebug();
}

void GameRenderManager::DrawDebugLine(const Color& color, const Line<int>& line) const
{
	DrawDebugLine(color, line.GetOrigin(), line.GetEnd());
}

void GameRenderManager::DrawDebugLines(const Color& color, const std::vector<Vector2<int>>& points) const
{
	m_renderSystem->StartDrawingToDebug();
	SetDrawColor(color);
	
	std::vector<SDL_Point> sdlPoints(points.size());
	for (size_t i = 0; i < points.size(); ++i)
	{
		sdlPoints[i] = { points[i].x, points[i].y };
	}

	SDL_RenderDrawLines(m_renderSystem->GetRenderer(), &*sdlPoints.begin(), sdlPoints.size());
	m_renderSystem->StopDrawingToDebug();
}

void GameRenderManager::DrawDebugRect(const Color& color, const Rect<int>& rect) const
{
	m_renderSystem->StartDrawingToDebug();
	SetDrawColor(color);
	SDL_Rect sdlRect = rect.ToSDLRect();
	SDL_RenderDrawRect(m_renderSystem->GetRenderer(), &sdlRect);
	m_renderSystem->StopDrawingToDebug();
}



SDL_Texture* GameRenderManager::LoadImageTexture(const ImageResourceData& imageResourceData) const
{
	SDL_Surface* surface = IMG_Load(imageResourceData.p_sourcePath.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderSystem->GetRenderer(), surface);
	if (imageResourceData.p_alphaTransparency)
	{
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	}

	SDL_FreeSurface(surface);

	return texture;
}

SDL_Texture* GameRenderManager::LoadTextTexture(const TextResourceData& textResourceData,
												const std::string& text, const int pointSize, const Color& color,
												Vector2<int>& outTextSize) const
{
	const char* pathString = textResourceData.p_sourcePath.c_str();
	const char* textString = text.c_str();

	TTF_Font* font = TTF_OpenFont(pathString, pointSize);
	SDL_Surface* surface = TTF_RenderText_Blended(font, textString, color.ToSDLColor());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderSystem->GetRenderer(), surface);
	SDL_FreeSurface(surface);
	TTF_SizeText(font, textString, &outTextSize.x, &outTextSize.y);

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

void GameRenderManager::UpdateRendererQueue()
{
	for (auto it = m_renderersQueue.begin(); it != m_renderersQueue.end(); ++it)
	{
		(*it)->Update();
	}
}

void GameRenderManager::DrawRendererQueue()
{
	SDL_SetRenderDrawBlendMode(m_renderSystem->GetRenderer(), SDL_BLENDMODE_BLEND); // Always draw transparents (for now)

	for (auto it = m_renderersQueue.begin(); it != m_renderersQueue.end(); ++it)
	{
		(*it)->Render(m_renderSystem->GetRenderer());
	}
}




void GameRenderManager::SetDrawColor(const Color& color) const
{
	SDL_SetRenderDrawColor(m_renderSystem->GetRenderer(), color.r, color.g, color.b, color.a);
}
