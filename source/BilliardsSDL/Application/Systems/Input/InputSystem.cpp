#include "InputSystem.h"

InputSystem::InputSystem()
	: m_windowInputs(), m_sdlKeysMap(3), m_keyStatesByCode(3), m_mouseScreenPosition{0,0},
	m_window(nullptr)
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::Init(SDL_Window* window)
{
	m_window = window;

	AddKeyEntry(SDL_BUTTON_LEFT, KeyCode::MouseLeft);
	AddKeyEntry(SDL_BUTTON_RIGHT, KeyCode::MouseRight);
	AddKeyEntry(SDLK_ESCAPE, KeyCode::Esc);
	AddKeyEntry(SDLK_SPACE, KeyCode::Space);
	AddKeyEntry(SDLK_c, KeyCode::C);
	AddKeyEntry(SDLK_r, KeyCode::R);
}

void InputSystem::AddKeyEntry(const SDL_Keycode sdlKeyCode, const KeyCode keyCode)
{
	m_sdlKeysMap[sdlKeyCode] = keyCode;
	m_keyStatesByCode[keyCode] = KeyState{};
}




void InputSystem::Update()
{
	UpdatePreviousState();
	ProcessEvents();
}

void InputSystem::UpdatePreviousState()
{
	for (auto keyStateIt = m_keyStatesByCode.begin(); keyStateIt != m_keyStatesByCode.end(); ++keyStateIt)
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
			m_mouseScreenPosition.x = polledEvent.motion.x;
			m_mouseScreenPosition.y = polledEvent.motion.y;
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
	auto keyCodeIt = m_sdlKeysMap.find(sdlKeyCode);
	if (keyCodeIt == m_sdlKeysMap.end())
	{
		return;
	}

	KeyState* keyState = &(m_keyStatesByCode.find(keyCodeIt->second)->second);
	keyState->SetPressed(isPressed);
}

void InputSystem::UpdateWindowEvent(const Uint8 windowEventId)
{
	if (windowEventId == SDL_WindowEventID::SDL_WINDOWEVENT_CLOSE)
	{
		m_windowInputs.p_closeWindow = true;
	}
}



const WindowInputs& InputSystem::GetWindowInputs()
{
	return m_windowInputs;
}




bool InputSystem::GetKeyDown(const KeyCode keyCode)
{
	return m_keyStatesByCode.find(keyCode)->second.WasPressedThisFrame();
}

bool InputSystem::GetKey(const KeyCode keyCode)
{
	return m_keyStatesByCode.find(keyCode)->second.IsPressed();
}

bool InputSystem::GetKeyUp(const KeyCode keyCode)
{
	return m_keyStatesByCode.find(keyCode)->second.WasReleasedThisFrame();
}

const Vector2<int> InputSystem::GetMouseScreenPosition() const
{
	return m_mouseScreenPosition;
}
