#include "Timer.h"

Timer::Timer(const float& duration)
	: m_duration(duration), m_currentTime(0.0f)
{}

Timer::~Timer()
{}



void Timer::SetDuration(const float& duration)
{
	m_duration = duration;
}

float Timer::GetDuration() const
{
	return m_duration;
}

void Timer::ClearTime()
{
	m_currentTime = 0.0f;
}

void Timer::Update(const float& deltaTime)
{
	m_currentTime += deltaTime;
}

bool Timer::HasFinished() const
{
	return m_currentTime >= m_duration;
}

float Timer::GetRatio01() const
{
	return Math::Clamp01(m_currentTime / m_duration);
}
