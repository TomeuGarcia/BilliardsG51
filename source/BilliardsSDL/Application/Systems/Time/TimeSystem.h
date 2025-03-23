#pragma once
#include <chrono>
#include "ITimeState.h"

class TimeSystem : public ITimeState
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
	std::chrono::system_clock::time_point m_applicationInitTime;
	std::chrono::system_clock::time_point m_previousTime;
	std::chrono::system_clock::time_point m_currentTime;
	
	float m_time;
	float m_deltaTime;
};