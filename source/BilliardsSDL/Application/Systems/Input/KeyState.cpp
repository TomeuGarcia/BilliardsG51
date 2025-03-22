#include "KeyState.h"

KeyState::KeyState()
	: _isPressed(false), _wasPressed(false)
{
}

KeyState::~KeyState()
{
}

void KeyState::UpdatePrevious()
{
	_wasPressed = _isPressed;
}

void KeyState::SetPressed(const bool isPressed)
{
	_isPressed = isPressed;
}

bool KeyState::WasPressedThisFrame()
{
	return _isPressed && !_wasPressed;
}

bool KeyState::IsPressed()
{
	return _isPressed;
}

bool KeyState::WasReleasedThisFrame()
{
	return !_isPressed && _wasPressed;
}
