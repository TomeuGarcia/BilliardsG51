#pragma once
#include "Camera2D.h"
#include "CameraShaker.h"

class ICameraFunctionalities
{
public:
	virtual ICameraShakePlayer* const GetCameraShakePlayer() = 0;
	virtual Camera2D* const GetMainCamera() = 0;
};