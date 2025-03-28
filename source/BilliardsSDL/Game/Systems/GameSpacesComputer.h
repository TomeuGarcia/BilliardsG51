#pragma once
#include "../../Application/Systems/Render/RenderSystem.h"
#include "../../Shared/Types/Vector2/Vector2.h"
#include "../../Shared/Types/Rect/Rect.h"


class GameSpacesComputer
{
public:
	GameSpacesComputer(RenderSystem* renderSystem, float worldWidthInWindow);
	~GameSpacesComputer();

public:
	static GameSpacesComputer* GetInstance();

public:
	void Update();

	Vector2<int> WorldToWindowPosition(const Vector2<float>& worldPosition);
	Vector2<float> WindowToWorldPosition(const Vector2<int>& windowPosition);

	Vector2<int> WorldToWindowVector(const Vector2<float>& worldVector);
	Vector2<float> WindowToWorldVector(const Vector2<int>& windowVector);

	Rect<int> WorldToWindowRect(const Rect<float>& worldRect);
	Rect<float> WindowToWorldRect(const Rect<int>& windowRect);

	Line<int> WorldToWindowLine(const Line<float>& worldLine);


private:
	RenderSystem* m_renderSystem;
	float m_worldWidthInWindow;
	float m_pixelsPerWorldUnit;
	Vector2<int> m_halfWindowSize;

private:
	static GameSpacesComputer* s_instance;
};
