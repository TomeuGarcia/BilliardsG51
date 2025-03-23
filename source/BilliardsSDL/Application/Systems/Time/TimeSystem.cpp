#include "TimeSystem.h"

TimeSystem::TimeSystem()
	: m_applicationInitTime(), m_previousTime(), m_currentTime(),
	m_time(0), m_deltaTime(0)
{
	auto xd = std::chrono::system_clock::now();
	std::chrono::duration<float> duration = xd - xd;
}

TimeSystem::~TimeSystem()
{
}

void TimeSystem::Init()
{
	m_applicationInitTime = m_currentTime = GetCurrentTime();
}

void TimeSystem::Update()
{
	m_previousTime = m_currentTime;
	m_currentTime = GetCurrentTime();

	std::chrono::duration<float> elapsedTime = m_currentTime - m_previousTime;

	m_deltaTime = elapsedTime.count();
	m_time += m_deltaTime;
}

const std::chrono::system_clock::time_point TimeSystem::GetCurrentTime() const
{
	return std::chrono::system_clock::now();
}

float TimeSystem::GetTime()
{
	return m_time;
}

float TimeSystem::GetDeltaTime()
{
	return m_deltaTime;
}
