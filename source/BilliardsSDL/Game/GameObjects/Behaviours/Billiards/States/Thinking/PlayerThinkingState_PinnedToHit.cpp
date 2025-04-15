#include "PlayerThinkingState_PinnedToHit.h"


PlayerThinkingState_PinnedToHit::PlayerThinkingState_PinnedToHit(BilliardsGameplayStateBlackboard* blackboard, BilliardsPlayer* player)
	: PlayerThinkingState(blackboard, player)
{
}

void PlayerThinkingState_PinnedToHit::DoEnter()
{
	m_pinPosition = GetBlackboard()->GetCanHitWhiteBall() 
		? GetBlackboard()->GetWhiteBallPosition()
		: GameInput::GetInstance()->GetMouseWorldPosition();
}

bool PlayerThinkingState_PinnedToHit::Update()
{
	Vector2<float> currentMousePosition = GameInput::GetInstance()->GetMouseWorldPosition();

	Vector2<float> currentToPin = m_pinPosition - currentMousePosition;
	float currentToPinDistance = currentToPin.Length();
	Vector2<float> currentToPinDirection = currentToPinDistance < 0.01f ? Vector2<float>::Up() : (currentToPin / currentToPinDistance);


	float pinDragDistance = Math::Min(GetBlackboard()->GetPinPullMaxDistance(), currentToPinDistance);
	Vector2<float> tipPosition = m_pinPosition;
	tipPosition -= currentToPinDirection * pinDragDistance;


	Color pinLineColor = GetBlackboard()->GetCanHitWhiteBall()
		? Colors::Orange
		: Colors::DarkPurple;

	GetPlayer()->GetStick()->SetTipPositionAndLookDirection(tipPosition, currentToPinDirection);
	GameRenderManager::GetInstance()->DrawDebugLine(
		pinLineColor, GameSpacesComputer::GetInstance()->WorldToWindowLine(Line<float>(m_pinPosition, tipPosition))
	);

	GetBlackboard()->p_directionToPinPosition = currentToPinDirection;



	if (GameInput::GetInstance()->GetKeyUp(KeyCode::MouseRight))
	{
		SetNextState(Type::MovingAround);
		return true;
	}

	if (GameInput::GetInstance()->GetKeyUp(KeyCode::MouseLeft))
	{
		if (pinDragDistance < GetBlackboard()->GetPinPullMinDistance())
		{
			SetNextState(Type::MovingAround);
			return true;
		}


		GetBlackboard()->p_pinPosition = m_pinPosition;
		GetBlackboard()->p_pinPullDistanceForHit = pinDragDistance;

		SetNextState(Type::Hitting);
		return true;
	}

	return false;
}

void PlayerThinkingState_PinnedToHit::Exit()
{}
