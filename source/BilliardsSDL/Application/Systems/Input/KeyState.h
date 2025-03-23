#pragma once

class KeyState
{
public:
	KeyState();
	~KeyState();

	void UpdatePrevious();
	void SetPressed(const bool isPressed);

	bool WasPressedThisFrame();
	bool IsPressed();
	bool WasReleasedThisFrame();	

private:
	bool m_wasPressed;
	bool m_isPressed;
};