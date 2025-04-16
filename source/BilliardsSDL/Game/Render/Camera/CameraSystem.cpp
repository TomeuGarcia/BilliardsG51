#include "CameraSystem.h"

CameraSystem::CameraSystem()
	: m_defaultCamera(), m_shakeCamera(),
	m_cameraTransformations(&m_shakeCamera),
	m_cameraShaker(CameraShaker::Config{ 1.0f, 2, 2.0f }, &m_shakeCamera)
{
}



void CameraSystem::Update(const float& deltaTime)
{
	m_cameraShaker.Update(deltaTime, &m_defaultCamera);
}



CameraTransformations* const CameraSystem::GetTransformations()
{
	return &m_cameraTransformations;
}

ICameraShakePlayer* const CameraSystem::GetCameraShakePlayer()
{
	return &m_cameraShaker;
}

Camera2D* const CameraSystem::GetMainCamera()
{
	return &m_defaultCamera;
}
