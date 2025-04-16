#pragma once
#include "../Colliders/Collider2D.h"


struct CollisionHit2D
{
	Collider2D* collider;
	Vector2<float> point;
	float distanceFromOrigin;
};