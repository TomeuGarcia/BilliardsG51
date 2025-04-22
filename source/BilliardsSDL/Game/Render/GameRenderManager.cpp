#include "GameRenderManager.h"

GameRenderManager* GameRenderManager::s_instance = nullptr;

GameRenderManager::GameRenderManager(RenderSystem* renderSystem, IGameSpacesComputer* gameSpacesComputer)
	: m_renderSystem(renderSystem), m_renderersQueue(), 
	m_cameraSystem(),
	m_outputRenderer(renderSystem->GetRenderer(), m_cameraSystem.GetTransformations(), gameSpacesComputer)
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



ICameraFunctionalities* GameRenderManager::GetCameraFunctionalities()
{
	return &m_cameraSystem;
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



void GameRenderManager::DrawGizmoLine(const Color& color, const Line<float>& line)
{
	DrawGizmoLine(color, line.GetOrigin(), line.GetEnd());
}

void GameRenderManager::DrawGizmoLine(const Color& color, const Vector2<float>& start, const Vector2<float>& end)
{
	m_renderSystem->StartDrawingToDebug();
	m_outputRenderer.DrawLine(color, start, end);
	m_renderSystem->StopDrawingToDebug();
}

void GameRenderManager::DrawGizmoLines(const Color& color, const std::vector<Vector2<float>>& points)
{
	m_renderSystem->StartDrawingToDebug();
	m_outputRenderer.DrawLines(color, points);
	m_renderSystem->StopDrawingToDebug();
}

void GameRenderManager::DrawGizmoRect(const Color& color, const Rect<float>& rect)
{
	m_renderSystem->StartDrawingToDebug();
	m_outputRenderer.DrawRect(color, rect);
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



void GameRenderManager::AddToRenderQueue(const std::shared_ptr<Renderer>& renderer)
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
		(*it)->Update(m_cameraSystem.GetTransformations());
	}
}

void GameRenderManager::UpdateState(const float& deltaTime)
{
	m_cameraSystem.Update(deltaTime);
}

void GameRenderManager::DrawRendererQueue()
{
	SDL_SetRenderDrawBlendMode(m_renderSystem->GetRenderer(), SDL_BLENDMODE_BLEND); // Always draw transparents (for now)

	for (auto it = m_renderersQueue.begin(); it != m_renderersQueue.end(); ++it)
	{
		Renderer* renderer = it->get();
		if (renderer->IsActive())
		{
			renderer->Render(&m_outputRenderer);
		}
	}
}

