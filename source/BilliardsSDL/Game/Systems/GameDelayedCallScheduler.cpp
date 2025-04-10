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
			schedulledCall.p_callable->PerformDelayedCall();
			m_schedulledCalls.erase(m_schedulledCalls.begin() + i);
		}
	}
}



void GameDelayedCallScheduler::AddCall(const float& delay, ICallable* callable)
{
	m_schedulledCalls.emplace_back(SchedulledCall{ Timer{delay}, callable });
}

void GameDelayedCallScheduler::RemoveCall(const ICallable* callable)
{
	for (auto it = m_schedulledCalls.begin(); it != m_schedulledCalls.end(); ++it)
	{
		if (it->p_callable == callable)
		{
			m_schedulledCalls.erase(it);
			return;
		}
	}
}
