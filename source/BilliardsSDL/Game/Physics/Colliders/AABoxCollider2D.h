#pragma once
#include "Collider2D.h"
#include "../../../Shared/Types/Rect/Rect.h"

class AABoxCollider2D : public Collider2D
{
public:
	AABoxCollider2D(GameObject* gameObject, Rigidbody2D* optionalRigidbody, const bool& isTrigger, 
		const Vector2<float>& size);
	virtual ~AABoxCollider2D();


	void SetSize(const Vector2<float>& size);
	const Rect<float>& GetShape() const;

	virtual void UpdateShape() override;


private:
	Rect<float> m_shape;
};