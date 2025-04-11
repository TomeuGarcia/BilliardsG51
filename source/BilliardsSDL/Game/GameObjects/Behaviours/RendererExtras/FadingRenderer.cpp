#include "FadingRenderer.h"

FadingRenderer::FadingRenderer(Renderer* renderer, const float& fadeDuration, 
	const float& goalAlpha, const Vector2<float>& moveAmount, const float& scaleAmount)
	: m_renderer(renderer), m_fadeTimer(fadeDuration), m_delayTimer(0.0f),
	m_startingColor(), m_goalColor(m_startingColor.WithAlpha(goalAlpha * 255)),
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

void FadingRenderer::StartShowingWithDelay(const Vector2<float>& position, const float& delay)
{
	m_delayTimer.SetDuration(delay);
	m_delayTimer.ClearTime();
	StartShowing(position);
}


void FadingRenderer::SetStartingColor(const Color& color)
{
	m_startingColor = color;
	m_renderer->SetColorTint(color);

	m_goalColor = color.WithAlpha(m_goalColor.a);
}


void FadingRenderer::Start()
{
	SetStartingColor(m_renderer->GetColorTint());
	m_startingScale = m_renderer->p_scale;
	m_goalScale = m_renderer->p_scale * m_scaleAmount;
}

void FadingRenderer::Update()
{
	const float deltaTime = GameTime::GetInstance()->GetDeltaTime();

	if (!m_delayTimer.HasFinished())
	{
		m_delayTimer.Update(deltaTime);
		return;
	}

	if (m_fadeTimer.HasFinished())
	{
		m_renderer->SetColorTint(m_goalColor);
		return;
	}

	m_fadeTimer.Update(deltaTime);
	float t = m_fadeTimer.GetRatio01();
	t *= t;

	m_renderer->SetColorTint(Color::LerpAlpha(m_startingColor, m_goalColor.a, t));
	m_renderer->p_scale = Vector2<float>::Lerp(m_startingScale, m_goalScale, t);
	m_renderer->GetTransform()->p_worldPosition = Vector2<float>::Lerp(m_startingPosition, m_goalPosition, t);
}

GameObject* FadingRenderer::GetGameObject()
{
	return m_renderer->GetGameObject();
}
