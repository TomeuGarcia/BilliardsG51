#include "PlayerThinkingState_MovingAround.h"


PlayerThinkingState_MovingAround::PlayerThinkingState_MovingAround(BilliardsGameplayStateBlackboard* blackboard, BilliardsPlayer* player)
	: PlayerThinkingState(blackboard, player)
{
}

void PlayerThinkingState_MovingAround::DoEnter()
{
}

bool PlayerThinkingState_MovingAround::Update()
{
	Vector2<float> currentMousePosition = GameInput::GetInstance()->GetMouseWorldPosition();

	if (GameInput::GetInstance()->GetKeyDown(KeyCode::MouseLeft))
	{
		SetNextState(Type::PinnedToHit);
		return true;
	}


	GetPlayer()->GetStick()->SetTipPositionAndLookDirection(currentMousePosition, Vector2<float>::Up());

	return false;
}

void PlayerThinkingState_MovingAround::Exit()
{
}
