#include "Text.h"

Text::Text(GameObject* gameObject, const std::string& text, const int pointSize)
	: Renderer(gameObject, Vector2<float>::Zero()), m_text(text), m_pointSize(pointSize)
{
}

Text::~Text()
{
}

void Text::Init(const GameRenderManager& renderManager, const TextResourceData& resourceData)
{
	Vector2<int> windowSize;
	InitTexture(renderManager.LoadTextTexture(resourceData, m_text, m_pointSize, Colors::White, windowSize));
	r_worldSize = GameSpacesComputer::GetInstance()->WindowToWorldVector(windowSize);
}

void Text::Reset(const GameRenderManager& renderManager, const TextResourceData& resourceData, const std::string& text)
{
	CleanupTexture();
	m_text = text;
	Init(renderManager, resourceData);
}


SDL_Rect* Text::GetSourceRect()
{
	return NULL;
}