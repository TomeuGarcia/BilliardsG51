#pragma once
#include <vector>
#include <functional>
#include "../../Shared/Timer/Timer.h"


class GameDelayedCallScheduler
{
public:
	class ICallable
	{
	public:
		virtual void PerformDelayedCall() = 0;
	};

private:
	struct SchedulledCall
	{
	public:
		Timer p_timer;
		ICallable* p_callable;
	};


public:
	GameDelayedCallScheduler();
	~GameDelayedCallScheduler();

	static GameDelayedCallScheduler* GetInstance();


public:
	void Update(const float& deltaTime);

public:
	void AddCall(const float& delay, ICallable* callable);
	void RemoveCall(const ICallable* callable);


private:
	std::vector<SchedulledCall> m_schedulledCalls;

private:
	static GameDelayedCallScheduler* s_instance;
};