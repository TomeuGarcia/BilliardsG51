#pragma once
#include <SDL.h>
#include <unordered_map>

#include "WindowInputs.h"
#include "KeyState.h"
#include "IInputState.h"


class InputSystem : public IInputState
{
public:
	InputSystem();
	~InputSystem();
	void Init(SDL_Window* window);
private:
	void AddKeyEntry(const SDL_Keycode sdlKeyCode, const KeyCode keyCode);


public:
	void Update();
	bool WindowStopFocus();


private:
	void UpdatePreviousState();
	void ProcessEvents();
	void UpdateKeyState(const SDL_Keycode sdlKeyCode, const bool isPressed);
	void UpdateWindowEvent(const Uint8 windowEventId);


public:
	const WindowInputs& GetWindowInputs();

	
public:
	virtual bool GetKeyDown(const KeyCode keyCode) override;
	virtual bool GetKey(const KeyCode keyCode) override;
	virtual bool GetKeyUp(const KeyCode keyCode) override;
	virtual const Vector2<int> GetMouseScreenPosition() const override;


private:		
	SDL_Window* m_window;

	WindowInputs m_windowInputs;

	std::unordered_map<SDL_Keycode, KeyCode> m_sdlKeysMap;
	std::unordered_map<KeyCode, KeyState> m_keyStatesByCode;

	Vector2<int> m_mouseScreenPosition;
};