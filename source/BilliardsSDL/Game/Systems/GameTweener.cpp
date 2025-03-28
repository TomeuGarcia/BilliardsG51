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

Vector2<float> GameTweener::TransformTween::GetCurrentValue() const
{
	const float t = Math::Clamp01(m_currentTime / m_duration);
	return Vector2<float>::Lerp(m_origin, m_goal, t);
}

bool GameTweener::TransformTween::HasFinished()
{
	return m_currentTime >= m_duration;
}




GameTweener* GameTweener::s_instance = nullptr;

GameTweener::GameTweener()
	: m_positionTweens()
{
	m_positionTweens.reserve(30);

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
}

void GameTweener::Clear()
{
	m_positionTweens.clear();
}



void GameTweener::TweenPosition(Transform* transform, const Vector2<float>& goalPosition, const float& duration, const float& delay = 0.0f)
{
	m_positionTweens.emplace_back(transform, transform->p_worldPosition, goalPosition, duration, delay);
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
