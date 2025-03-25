#pragma once
#include "Collider2D.h"
#include "../../../Shared/Types/Rect/Rect.h"

class AABoxCollider2D : public Collider2D
{
public:
	AABoxCollider2D(GameObject* gameObject, Rigidbody2D* optionalRigidbody, const Vector2<float>& size);
	virtual ~AABoxCollider2D();


	void SetWidth(const float& width);
	void SetHeight(const float& height);
	const Rect<float>& GetShape() const;

	virtual void UpdateShape() override;


private:
	Rect<float> m_shape;
};