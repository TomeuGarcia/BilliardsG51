#pragma once
#include "Collider2D.h"
#include "../../../Shared/Types/Circle/Circle.h"


class CircleCollider2D : public Collider2D
{
public:
	CircleCollider2D(GameObject* gameObject, Rigidbody2D* optionalRigidbody, const float& radius);
	virtual ~CircleCollider2D();


	void SetRadius(const float& radius);
	const Circle& GetShape() const;

	virtual void UpdateShape() override;


private:
	Circle m_shape;

};