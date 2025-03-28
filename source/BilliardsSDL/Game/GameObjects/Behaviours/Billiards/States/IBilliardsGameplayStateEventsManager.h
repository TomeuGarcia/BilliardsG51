#pragma once
#include "../../../../../Shared/Types/Vector2/Vector2.h"


class IBilliardsGameplayStateEventsManager
{
public:
	virtual bool TryHitBalls(const Vector2<float>& position, const Vector2<float>& direction, 
		const float& forceMagnitude) = 0;
};