#pragma once
#include "../Behaviour.h"
#include "../../../Render/Renderers/Image/Image.h"
#include "../../../../Shared/Math/Math.h"


class BilliardStick : public Behaviour
{
public:
	BilliardStick(Transform* transform, Image* image, 
		const Vector2<float>& defaultImageDirection, 
		const float& stickDistanceToHandle, const float& stickDistanceToTip);
	virtual ~BilliardStick();

	virtual void Start() override;


	void SetTipPositionAndLookDirection(const Vector2<float>& tipPosition, const Vector2<float>& lookDirection);
	void SetResting();

private:
	Transform* m_transform;
	Image* m_image;
	Vector2<float> m_defaultImageDirection;
	float m_stickDistanceToHandle;
	float m_stickDistanceToTip;

	Vector2<float> m_restingPosition;
};