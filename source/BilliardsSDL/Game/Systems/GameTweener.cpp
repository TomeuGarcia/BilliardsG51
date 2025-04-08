#include "GameTweener.h"

GameTweener::TransformTween::TransformTween(Transform* transform, const Vector2<float>& origin, const Vector2<float>& goal, 
	const float& duration, const float& delay)
	: p_transform(transform), m_origin(origin), m_goal(goal), m_duration(duration), m_currentTime(0.0f - delay)
{
}

void GameTweener::TransformTween::Update(const float& deltaTime)
{
	m_currentTime += deltaTime;
}

void GameTweener::TransformTween::UpdateComplete()
{
	m_currentTime = m_duration;
}

Vector2<float> GameTweener::TransformTween::GetCurrentValue() const
{
	const float t = Math::Clamp01(m_currentTime / m_duration);
	return Vector2<float>::Lerp(m_origin, m_goal, t);
}

bool GameTweener::TransformTween::HasFinished()
{
	return m_currentTime >= m_duration;
}



GameTweener::RendererColorTween::RendererColorTween(Renderer* renderer, const Color& origin, const Color& goal, 
	const float& duration, const float& delay)
	: p_renderer(renderer), m_origin(origin), m_goal(goal), m_duration(duration), m_currentTime(0.0f - delay)
{}

void GameTweener::RendererColorTween::Update(const float& deltaTime)
{
	m_currentTime += deltaTime;
}

void GameTweener::RendererColorTween::UpdateComplete()
{
	m_currentTime = m_duration;
}

Color GameTweener::RendererColorTween::GetCurrentValue() const
{
	const float t = Math::Clamp01(m_currentTime / m_duration);
	return Color::Lerp(m_origin, m_goal, t);
}

bool GameTweener::RendererColorTween::HasFinished()
{
	return m_currentTime >= m_duration;
}





GameTweener* GameTweener::s_instance = nullptr;

GameTweener::GameTweener()
	: m_positionTweens(), 
	m_colorTweens()
{
	m_positionTweens.reserve(30);
	m_colorTweens.reserve(30);

	s_instance = this;
}

GameTweener::~GameTweener()
{
	s_instance = nullptr;
}

GameTweener* GameTweener::GetInstance()
{
	return s_instance;
}



void GameTweener::Update(const float& deltaTime)
{
	UpdatePositionTweens(deltaTime);
	UpdateColorTweens(deltaTime);
}

void GameTweener::Clear()
{
	m_positionTweens.clear();
	m_colorTweens.clear();
}



void GameTweener::TweenPosition(Transform* transform, const Vector2<float>& goalPosition, const float& duration, const float& delay)
{
	m_positionTweens.emplace_back(transform, transform->p_worldPosition, goalPosition, duration, delay);
}

void GameTweener::TweenColor(Renderer* renderer, const Color& goalColor, const float& duration, const float& delay)
{
	m_colorTweens.emplace_back(renderer, renderer->GetColorTint(), goalColor, duration, delay);
}



void GameTweener::CompletePosition(Transform* transform)
{
	for (auto it = m_positionTweens.begin(); it != m_positionTweens.end(); ++it)
	{
		if (it->p_transform == transform)
		{
			it->UpdateComplete();
			it->p_transform->p_worldPosition = it->GetCurrentValue();
			m_positionTweens.erase(it);
			return;
		}
	}
}

void GameTweener::CompleteColor(Renderer* renderer)
{
	for (auto it = m_colorTweens.begin(); it != m_colorTweens.end(); ++it)
	{
		if (it->p_renderer == renderer)
		{
			it->UpdateComplete();
			it->p_renderer->SetColorTint(it->GetCurrentValue());
			m_colorTweens.erase(it);
			return;
		}
	}
}



void GameTweener::UpdatePositionTweens(const float& deltaTime)
{	
	for (auto it = m_positionTweens.begin(); it != m_positionTweens.end(); )
	{
		TransformTween& tween = *it;
		tween.Update(deltaTime);
		tween.p_transform->p_worldPosition = tween.GetCurrentValue();

		if (tween.HasFinished())
		{
			it = m_positionTweens.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void GameTweener::UpdateColorTweens(const float& deltaTime)
{
	for (auto it = m_colorTweens.begin(); it != m_colorTweens.end(); )
	{
		RendererColorTween& tween = *it;
		tween.Update(deltaTime);
		tween.p_renderer->SetColorTint(tween.GetCurrentValue());

		if (tween.HasFinished())
		{
			it = m_colorTweens.erase(it);
		}
		else
		{
			++it;
		}
	}
}

