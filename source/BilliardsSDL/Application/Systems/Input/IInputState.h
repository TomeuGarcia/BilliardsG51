#pragma once
#include "KeyCode.h"
#include "../../../Shared/Types/Vector2/Vector2.h"

class IInputState
{
public:
	virtual bool GetKeyDown(const KeyCode keyCode) = 0;
	virtual bool GetKey(const KeyCode keyCode) = 0;
	virtual bool GetKeyUp(const KeyCode keyCode) = 0;

	virtual const Vector2<int> GetMouseScreenPosition() const = 0;
};