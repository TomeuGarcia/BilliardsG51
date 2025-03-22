#pragma once
#include <SDL.h>
#include <unordered_map>

#include "WindowInputs.h"
#include "KeyState.h"
#include "IInputState.h"

class InputSystem : IInputState
{
public:
	InputSystem();
	~InputSystem();
	void Init();
private:
	void AddKeyEntry(const SDL_Keycode sdlKeyCode, const KeyCode keyCode);


public:
	void Update();
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


private:		
	WindowInputs _windowInputs;

	std::unordered_map<SDL_Keycode, KeyCode> _sdlKeysMap;
	std::unordered_map<KeyCode, KeyState> _keyStatesByCode;

	int _mouseScreenPositionX;
	int _mouseScreenPositionY;
};