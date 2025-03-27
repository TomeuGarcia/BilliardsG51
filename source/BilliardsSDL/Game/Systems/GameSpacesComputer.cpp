#include "GameSpacesComputer.h"

GameSpacesComputer* GameSpacesComputer::s_instance = nullptr;

GameSpacesComputer::GameSpacesComputer(RenderSystem* renderSystem, float worldWidthInWindow)
	: m_renderSystem(renderSystem), m_worldWidthInWindow(worldWidthInWindow), 
	m_pixelsPerWorldUnit(0), m_halfWindowSize()
{
	s_instance = this;
}

GameSpacesComputer::~GameSpacesComputer()
{
	s_instance = nullptr;
}



GameSpacesComputer* GameSpacesComputer::GetInstance()
{
	return s_instance;
}



void GameSpacesComputer::Update()
{
	const Vector2<int> windowSize{ m_renderSystem->GetWindowSize() };
	m_halfWindowSize = windowSize / 2;
	m_pixelsPerWorldUnit = windowSize.x / m_worldWidthInWindow;
}



Vector2<int> GameSpacesComputer::WorldToWindowPosition(const Vector2<float>& worldPosition)
{
	Vector2<int> windowPosition{};
	windowPosition.x = (worldPosition.x * m_pixelsPerWorldUnit) + m_halfWindowSize.x;
	windowPosition.y = (-worldPosition.y * m_pixelsPerWorldUnit) + m_halfWindowSize.y;

	return windowPosition;
}

Vector2<float> GameSpacesComputer::WindowToWorldPosition(const Vector2<int>& windowPosition)
{
	Vector2<float> worldPosition{};
	worldPosition.x = (windowPosition.x - m_halfWindowSize.x) / m_pixelsPerWorldUnit;
	worldPosition.y = -(windowPosition.y - m_halfWindowSize.y) / m_pixelsPerWorldUnit;

	return worldPosition;
}



Vector2<int> GameSpacesComputer::WorldToWindowVector(const Vector2<float>& worldVector)
{
	Vector2<int> windowVector{};
	windowVector.x = worldVector.x * m_pixelsPerWorldUnit;
	windowVector.y = -worldVector.y * m_pixelsPerWorldUnit;

	return windowVector;
}

Vector2<float> GameSpacesComputer::WindowToWorldVector(const Vector2<int>& windowVector)
{
	Vector2<float> worldVector{};
	worldVector.x = (float)windowVector.x / m_pixelsPerWorldUnit;
	worldVector.y = (float)windowVector.y / m_pixelsPerWorldUnit;

	return worldVector;
}



Rect<int> GameSpacesComputer::WorldToWindowRect(const Rect<float>& worldRect)
{
	Rect<int> windowRect{
		WorldToWindowPosition(worldRect.GetCenterPosition()),
		WorldToWindowVector(worldRect.GetSize())
	};

	return windowRect;
}

Rect<float> GameSpacesComputer::WindowToWorldRect(const Rect<int>& windowRect)
{
	Rect<float> worldRect{
		WindowToWorldPosition(windowRect.GetCenterPosition()),
		WindowToWorldVector(windowRect.GetSize())
	};

	return worldRect;
}

