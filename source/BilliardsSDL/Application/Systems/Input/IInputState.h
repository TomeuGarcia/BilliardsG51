#pragma once
#include "KeyCode.h"

class IInputState
{
	virtual bool GetKeyDown(const KeyCode keyCode) = 0;
	virtual bool GetKey(const KeyCode keyCode) = 0;
	virtual bool GetKeyUp(const KeyCode keyCode) = 0;
};