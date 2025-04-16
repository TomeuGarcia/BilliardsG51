#pragma once
#include "../../../Shared/Types/Vector2/Vector2.h"
#include "Camera2D.h"


class CameraTransformations
{
public:
	CameraTransformations(Camera2D* camera);


	Vector2<float> ApplyToWorldPosition(const Vector2<float>& worldPosition);


private:
	Camera2D* m_camera;
};