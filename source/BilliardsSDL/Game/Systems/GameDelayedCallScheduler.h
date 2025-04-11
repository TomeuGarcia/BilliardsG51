#pragma once
#include <vector>
#include <functional>
#include "../../Shared/Timer/Timer.h"


class GameDelayedCallScheduler
{
public:
	class ICallSource {};

private:
	struct SchedulledCall
	{
	public:
		Timer p_timer;
		ICallSource* p_callSource;
		std::function<void()> p_callback;
	};


public:
	GameDelayedCallScheduler();
	~GameDelayedCallScheduler();

	static GameDelayedCallScheduler* GetInstance();


public:
	void Update(const float& deltaTime);

public:
	void AddCall(ICallSource* callSource, const float& delay, const std::function<void()>& callback);
	void RemoveAllCalls(const ICallSource* callSource);


private:
	std::vector<SchedulledCall> m_schedulledCalls;

private:
	static GameDelayedCallScheduler* s_instance;
};