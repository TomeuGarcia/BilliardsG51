#pragma once
#include "../Math/Math.h"


class Timer
{
public:
	Timer(const float& duration);
	~Timer();

	void SetDuration(const float& duration);
	void ClearTime();


	void Update(const float& deltaTime);
	bool HasFinished() const;

	float GetRatio01() const;


private:
	float m_duration;
	float m_currentTime;
};