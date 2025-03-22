#include "TimeSystem.h"

TimeSystem::TimeSystem()
	: _applicationInitTime(), _previousTime(), _currentTime(),
	_time(0), _deltaTime(0)
{
	auto xd = std::chrono::system_clock::now();
	std::chrono::duration<float> duration = xd - xd;
}

TimeSystem::~TimeSystem()
{
}

void TimeSystem::Init()
{
	_applicationInitTime = _currentTime = GetCurrentTime();
}

void TimeSystem::Update()
{
	_previousTime = _currentTime;
	_currentTime = GetCurrentTime();

	_deltaTime = (_currentTime - _previousTime).count();
	_time += _deltaTime;
}

const std::chrono::system_clock::time_point TimeSystem::GetCurrentTime() const
{
	return std::chrono::system_clock::now();
}

float TimeSystem::GetTime()
{
	return _time;
}

float TimeSystem::GetDeltaTime()
{
	return _deltaTime;
}
