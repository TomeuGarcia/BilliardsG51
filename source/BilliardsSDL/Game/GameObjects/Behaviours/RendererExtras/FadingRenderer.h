#pragma once
#include "../Behaviour.h"
#include "../../../Render/Renderers/Renderer.h"
#include "../../../../Shared/Timer/Timer.h"

#include "../../../Systems/GameTime.h"


class FadingRenderer : public Behaviour
{
public:
	FadingRenderer(Renderer* renderer, const float& fadeDuration, const Vector2<float>& moveAmount, const float& scaleAmount);

	void StartShowing(const Vector2<float>& position);
	void SetStartingColor(const Color& color);

	virtual void Start() override;
	virtual void Update() override;

private:
	Renderer* m_renderer;
	Timer m_fadeTimer;

	Color m_startingColor;
	
	Vector2<float> m_moveAmount;
	Vector2<float> m_startingPosition;
	Vector2<float> m_goalPosition;

	float m_scaleAmount;
	Vector2<float> m_startingScale;
	Vector2<float> m_goalScale;
};