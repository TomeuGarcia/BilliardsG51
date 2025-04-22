#include "CameraTransformations.h"


CameraTransformations::CameraTransformations(Camera2D* camera)
	: m_camera(camera)
{
}

Vector2<float> CameraTransformations::ApplyToWorldPosition(const Vector2<float>& worldPosition)
{ 
	return worldPosition - m_camera->GetWorldPosition();
}
