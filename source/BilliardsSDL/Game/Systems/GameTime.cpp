#include "GameTime.h"


GameTime* GameTime::s_instance = nullptr;

GameTime::GameTime(ITimeState* timeState)
    : m_timeState(timeState)
{
    s_instance = this;
}

GameTime::~GameTime()
{
    s_instance = nullptr;
}



GameTime* GameTime::GetInstance()
{
    return s_instance;
}


float GameTime::GetTime() const
{
    return m_timeState->GetTime();
}

float GameTime::GetDeltaTime() const
{
    return m_timeState->GetDeltaTime();
}

