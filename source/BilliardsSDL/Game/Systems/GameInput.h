#pragma once
#include "../../Application/Systems/Input/IInputState.h"
#include "GameSpacesComputer.h"


class GameInput
{
public:
	GameInput(IInputState* inputState);
	~GameInput();

public:
	static GameInput* GetInstance();

public:
	bool GetKeyDown(const KeyCode keyCode);
	bool GetKey(const KeyCode keyCode);
	bool GetKeyUp(const KeyCode keyCode);
	const Vector2<int> GetMouseWindowPosition() const;
	const Vector2<float> GetMouseWorldPosition() const;



private:
	IInputState* m_inputState;

private:
	static GameInput* s_instance;
};