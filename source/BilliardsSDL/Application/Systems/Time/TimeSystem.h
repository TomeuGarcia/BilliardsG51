#pragma once
#include <chrono>
#include "ITimeState.h"

class TimeSystem : ITimeState
{
public: 
	TimeSystem();
	~TimeSystem();

	void Init();
	void Update();

	virtual float GetTime() override;
	virtual float GetDeltaTime() override;

private:
	const std::chrono::system_clock::time_point GetCurrentTime() const;


private:
	std::chrono::system_clock::time_point _applicationInitTime;
	std::chrono::system_clock::time_point _previousTime;
	std::chrono::system_clock::time_point _currentTime;
	
	float _time;
	float _deltaTime;
};