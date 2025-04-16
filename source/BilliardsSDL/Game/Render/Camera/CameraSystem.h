#pragma once
#include "CameraTransformations.h" 
#include "Camera2D.h"
#include "CameraShaker.h"
#include "ICameraFunctionalities.h"


class CameraSystem : public ICameraFunctionalities
{
public:
	CameraSystem();

	void Update(const float& deltaTime);

	CameraTransformations* const GetTransformations();


public:
	virtual ICameraShakePlayer* const GetCameraShakePlayer() override;
	virtual Camera2D* const GetMainCamera() override;


private:
	Camera2D m_defaultCamera;
	Camera2D m_shakeCamera;
	CameraTransformations m_cameraTransformations;
	CameraShaker m_cameraShaker;
};