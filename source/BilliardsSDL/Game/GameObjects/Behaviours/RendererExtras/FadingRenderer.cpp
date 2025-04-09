#include "FadingRenderer.h"

FadingRenderer::FadingRenderer(Renderer* renderer, const float& fadeDuration, const Vector2<float>& moveAmount, const float& scaleAmount)
	: m_renderer(renderer), m_fadeTimer(fadeDuration),
	m_startingColor(),
	m_moveAmount(moveAmount), m_startingPosition(), m_goalPosition(),
	m_scaleAmount(scaleAmount), m_startingScale(), m_goalScale()
{
	m_fadeTimer.Update(m_fadeTimer.GetDuration());
}

void FadingRenderer::StartShowing(const Vector2<float>& position)
{
	m_startingPosition = position;
	m_goalPosition = position + m_moveAmount;
	
	m_renderer->SetColorTint(m_startingColor);

	m_fadeTimer.ClearTime();
}

void FadingRenderer::SetStartingColor(const Color& color)
{
	m_startingColor = color;
	m_renderer->SetColorTint(color);
}


void FadingRenderer::Start()
{
	SetStartingColor(m_renderer->GetColorTint());
	m_startingScale = m_renderer->p_scale;
	m_goalScale = m_renderer->p_scale * m_scaleAmount;
}

void FadingRenderer::Update()
{
	if (m_fadeTimer.HasFinished())
	{
		m_renderer->SetColorTint(Colors::Transparent);
		return;
	}

	m_fadeTimer.Update(GameTime::GetInstance()->GetDeltaTime());
	float t = m_fadeTimer.GetRatio01();
	t *= t;

	m_renderer->SetColorTint(Color::LerpAlpha(m_startingColor, 0.0f, t));
	m_renderer->p_scale = Vector2<float>::Lerp(m_startingScale, m_goalScale, t);
	m_renderer->GetTransform()->p_worldPosition = Vector2<float>::Lerp(m_startingPosition, m_goalPosition, t);
}
