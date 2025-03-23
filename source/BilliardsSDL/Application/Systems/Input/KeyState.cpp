#include "KeyState.h"

KeyState::KeyState()
	: m_isPressed(false), m_wasPressed(false)
{
}

KeyState::~KeyState()
{
}

void KeyState::UpdatePrevious()
{
	m_wasPressed = m_isPressed;
}

void KeyState::SetPressed(const bool isPressed)
{
	m_isPressed = isPressed;
}

bool KeyState::WasPressedThisFrame()
{
	return m_isPressed && !m_wasPressed;
}

bool KeyState::IsPressed()
{
	return m_isPressed;
}

bool KeyState::WasReleasedThisFrame()
{
	return !m_isPressed && m_wasPressed;
}
