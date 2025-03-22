#pragma once

class ITimeState
{
public:
	virtual float GetTime() = 0;
	virtual float GetDeltaTime() = 0;
};