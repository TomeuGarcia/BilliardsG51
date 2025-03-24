#pragma once
#include "../../Application/Systems/Time/TimeSystem.h"


class GameTime
{
public:
	GameTime(ITimeState* timeState);
	~GameTime();

public:
	static GameTime* GetInstance();

public:
	float GetTime() const;
	float GetDeltaTime() const;


private:
	ITimeState* m_timeState;

private:
	static GameTime* s_instance;
};