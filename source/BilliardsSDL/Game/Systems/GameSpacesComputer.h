#pragma once
#include "../../Application/Systems/Render/RenderSystem.h"
#include "../../Shared/Types/Vector2/Vector2.h"
#include "../../Shared/Types/Rect/Rect.h"

#include "../Render/IGameSpacesComputer.h"


class GameSpacesComputer : public IGameSpacesComputer
{
public:
	GameSpacesComputer(RenderSystem* renderSystem, float worldWidthInWindow);
	~GameSpacesComputer();

public:
	static GameSpacesComputer* GetInstance();

public:
	void Update();

public:
	virtual Vector2<int> WorldToWindowPosition(const Vector2<float>& worldPosition) override;
	virtual Vector2<float> WindowToWorldPosition(const Vector2<int>& windowPosition) override;

	virtual Vector2<int> WorldToWindowVector(const Vector2<float>& worldVector) override;
	virtual Vector2<float> WindowToWorldVector(const Vector2<int>& windowVector) override;

	virtual Rect<int> WorldToWindowRect(const Rect<float>& worldRect) override;
	virtual Rect<float> WindowToWorldRect(const Rect<int>& windowRect) override;

	virtual Line<int> WorldToWindowLine(const Line<float>& worldLine) override;


private:
	RenderSystem* m_renderSystem;
	float m_worldWidthInWindow;
	float m_pixelsPerWorldUnit;
	Vector2<int> m_halfWindowSize;

private:
	static GameSpacesComputer* s_instance;
};
