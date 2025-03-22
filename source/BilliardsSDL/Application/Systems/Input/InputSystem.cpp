#include "InputSystem.h"

InputSystem::InputSystem()
	: _windowInputs(), _sdlKeysMap(3), _keyStatesByCode(3), _mouseScreenPositionX(0), _mouseScreenPositionY(0)
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::Init()
{
	AddKeyEntry(SDL_BUTTON_LEFT, KeyCode::MouseLeft);
	AddKeyEntry(SDL_BUTTON_RIGHT, KeyCode::MouseRight);
	AddKeyEntry(SDLK_ESCAPE, KeyCode::Esc);
}

void InputSystem::AddKeyEntry(const SDL_Keycode sdlKeyCode, const KeyCode keyCode)
{
	_sdlKeysMap[sdlKeyCode] = keyCode;
	_keyStatesByCode[keyCode] = KeyState{};
}




void InputSystem::Update()
{
	UpdatePreviousState();
	ProcessEvents();
}

void InputSystem::UpdatePreviousState()
{
	for (auto keyStateIt = _keyStatesByCode.begin(); keyStateIt != _keyStatesByCode.end(); ++keyStateIt)
	{
		keyStateIt->second.UpdatePrevious();
	}
}

void InputSystem::ProcessEvents()
{
	SDL_Event polledEvent;
	while (SDL_PollEvent(&polledEvent))
	{
		if (polledEvent.motion.type == SDL_MOUSEMOTION)
		{
			_mouseScreenPositionX = polledEvent.motion.x;
			_mouseScreenPositionY = polledEvent.motion.y;
		}
		else if (polledEvent.type == SDL_MOUSEBUTTONDOWN)
		{
			UpdateKeyState(polledEvent.button.button, true);
		}
		else if (polledEvent.type == SDL_MOUSEBUTTONUP)
		{
			UpdateKeyState(polledEvent.button.button, false);
		}
		else if (polledEvent.type == SDL_WINDOWEVENT)
		{
			UpdateWindowEvent(polledEvent.window.event);
		}
		else
		{
			SDL_Keycode keyCode{ polledEvent.key.keysym.sym };
			bool keyDown = polledEvent.key.type == SDL_KEYDOWN;
			UpdateKeyState(keyCode, keyDown);
		}
	}
}

void InputSystem::UpdateKeyState(const SDL_Keycode sdlKeyCode, const bool isPressed)
{
	auto keyCodeIt = _sdlKeysMap.find(sdlKeyCode);
	if (keyCodeIt == _sdlKeysMap.end())
	{
		return;
	}

	KeyState* keyState = &(_keyStatesByCode.find(keyCodeIt->second)->second);
	keyState->SetPressed(isPressed);
}

void InputSystem::UpdateWindowEvent(const Uint8 windowEventId)
{
	if (windowEventId == SDL_WindowEventID::SDL_WINDOWEVENT_CLOSE)
	{
		_windowInputs.closeWindow = true;
	}
}



const WindowInputs& InputSystem::GetWindowInputs()
{
	return _windowInputs;
}




bool InputSystem::GetKeyDown(const KeyCode keyCode)
{
	return _keyStatesByCode.find(keyCode)->second.WasPressedThisFrame();
}

bool InputSystem::GetKey(const KeyCode keyCode)
{
	return _keyStatesByCode.find(keyCode)->second.IsPressed();
}

bool InputSystem::GetKeyUp(const KeyCode keyCode)
{
	return _keyStatesByCode.find(keyCode)->second.WasReleasedThisFrame();
}