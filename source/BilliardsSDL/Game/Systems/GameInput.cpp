#include "GameInput.h"


GameInput* GameInput::s_instance = nullptr;

GameInput::GameInput(IInputState* inputState)
	: m_inputState(inputState)
{
	s_instance = this;
}

GameInput::~GameInput()
{
	s_instance = nullptr;
}



GameInput* GameInput::GetInstance()
{
	return s_instance;
}



bool GameInput::GetKeyDown(const KeyCode keyCode)
{
	return m_inputState->GetKeyDown(keyCode);
}

bool GameInput::GetKey(const KeyCode keyCode)
{
	return m_inputState->GetKey(keyCode);
}

bool GameInput::GetKeyUp(const KeyCode keyCode)
{
	return m_inputState->GetKeyUp(keyCode);
}

const Vector2<int> GameInput::GetMouseScreenPosition() const
{
	return m_inputState->GetMouseScreenPosition();
}

