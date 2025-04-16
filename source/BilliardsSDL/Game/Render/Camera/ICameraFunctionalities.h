#pragma once
#include "Camera2D.h"
#include "CameraShaker.h"
#include "CameraShakeSettings.h"

class ICameraFunctionalities
{
public:
	virtual ICameraShakePlayer* const GetCameraShakePlayer() = 0;
	virtual CameraShakeSettings* GetCameraShakeSettings() = 0;

	virtual Camera2D* const GetMainCamera() = 0;
};