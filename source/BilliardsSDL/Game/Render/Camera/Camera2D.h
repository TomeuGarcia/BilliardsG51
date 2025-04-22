#pragma once
#include "../../../Shared/Types/Vector2/Vector2.h"


class Camera2D
{
public:
	Camera2D();

	Vector2<float> GetWorldPosition() const;
	void SetWorldPosition(const Vector2<float>& worldPosition);

	float GetRotationAnglesInDegrees() const;
	void SetrotationAngles(const float& rotationAnglesInDegrees);


private:
	Vector2<float> m_worldPosition;
	float m_rotationAnglesInDegrees;
};