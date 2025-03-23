#include "GameSystems.h"


GameSystems::GameSystems()
	: m_inputState(nullptr), m_renderManager(), m_timeState(nullptr)
{
}

GameSystems::GameSystems(IInputState* inputState, RenderSystem* renderSystem, ITimeState* timeState)
	: m_inputState(inputState), m_renderManager(renderSystem), m_timeState(timeState)
{
}

GameSystems::~GameSystems()
{
}

IInputState* const GameSystems::GetInputState()
{
	return m_inputState;
}

GameRenderManager* const GameSystems::GetRenderManager()
{
	return &m_renderManager;
}

ITimeState* const GameSystems::GetTimeState()
{
	return m_timeState;
}
