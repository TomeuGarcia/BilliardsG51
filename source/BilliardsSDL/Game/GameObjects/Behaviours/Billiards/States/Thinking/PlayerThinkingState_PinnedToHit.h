#pragma once
#include "PlayerThinkingState.h"
#include "../../../../../Physics/Physics2DManager.h"


class PlayerThinkingState_PinnedToHit : public PlayerThinkingState
{
public:
	PlayerThinkingState_PinnedToHit(BilliardsGameplayStateBlackboard* blackboard, BilliardsPlayer* player);

	virtual bool Update() override;
	virtual void Exit() override;

protected:
	virtual void DoEnter() override;

private:
	void PreviewHitDirection(const Vector2<float>& currentToPinDirection, const float& pinDragDistance);


private:
	Vector2<float> m_pinPosition;
};
