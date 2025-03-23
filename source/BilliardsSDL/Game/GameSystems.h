#pragma once
#include "../Application/Systems/Input/IInputState.h"
#include "../Application/Systems/Render/RenderSystem.h"
#include "../Application/Systems/Time/ITimeState.h"
#include "Render/GameRenderManager.h"

class GameSystems
{
public:
	GameSystems();
	GameSystems(IInputState* inputState, RenderSystem* renderSystem, ITimeState* timeState);
	~GameSystems();


	IInputState* const GetInputState();
	GameRenderManager* const GetRenderManager();
	ITimeState* const GetTimeState();


private:
	IInputState* m_inputState;
	GameRenderManager m_renderManager;
	ITimeState* m_timeState;

};