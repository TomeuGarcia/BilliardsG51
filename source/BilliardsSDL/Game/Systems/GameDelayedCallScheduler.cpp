#include "GameDelayedCallScheduler.h"


GameDelayedCallScheduler* GameDelayedCallScheduler::s_instance = nullptr;


GameDelayedCallScheduler::GameDelayedCallScheduler()
	: m_schedulledCalls()
{
	m_schedulledCalls.reserve(10);
	s_instance = this;
}

GameDelayedCallScheduler::~GameDelayedCallScheduler()
{
	s_instance = nullptr;
}

GameDelayedCallScheduler* GameDelayedCallScheduler::GetInstance()
{
	return s_instance;
}



void GameDelayedCallScheduler::Update(const float& deltaTime)
{
	for (int i = m_schedulledCalls.size() - 1; i >= 0; --i)
	{
		SchedulledCall& schedulledCall = m_schedulledCalls[i];
		schedulledCall.p_timer.Update(deltaTime);
		if (schedulledCall.p_timer.HasFinished())
		{
			schedulledCall.p_callback();
			m_schedulledCalls.erase(m_schedulledCalls.begin() + i);
		}
	}
}



void GameDelayedCallScheduler::AddCall(ICallSource* callSource, const float& delay, const std::function<void()>& callback)
{
	m_schedulledCalls.emplace_back(SchedulledCall{ Timer{delay}, callSource, callback });
}

void GameDelayedCallScheduler::RemoveAllCalls(const ICallSource* callSource)
{
	for (auto it = m_schedulledCalls.begin(); it != m_schedulledCalls.end();)
	{
		if (it->p_callSource == callSource)
		{
			it = m_schedulledCalls.erase(it);
		}
		else
		{
			++it;
		}
	}
}
