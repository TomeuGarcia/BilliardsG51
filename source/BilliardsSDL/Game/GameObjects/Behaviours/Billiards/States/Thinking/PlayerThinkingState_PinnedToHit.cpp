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

	GetBlackboard()->p_directionToPinPosition = currentToPinDirection;
	GetPlayer()->GetStick()->SetTipPositionAndLookDirection(tipPosition, currentToPinDirection);
	GameRenderManager::GetInstance()->DrawGizmoLine(pinLineColor, Line<float>(m_pinPosition, tipPosition));


	if (GetBlackboard()->GetCanHitWhiteBall() &&
		GetBlackboard()->GetPreviewHitDirectionIsVisible())
	{
		PreviewHitDirection(currentToPinDirection, pinDragDistance);
	}	


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


void PlayerThinkingState_PinnedToHit::PreviewHitDirection(const Vector2<float>& currentToPinDirection, const float& pinDragDistance)
{
	Vector2<float> hitPreviewOrigin = m_pinPosition + (currentToPinDirection * (GetBlackboard()->GetWhiteBallRadius() + 0.02f));
	Line<float> hitPreviewRay{ hitPreviewOrigin, currentToPinDirection, 100.0f };
	CollisionHit2D hit;
	if (Physics2DManager::GetInstance()->RaycastFirstHit(hitPreviewRay, hit))
	{
		float dragT = pinDragDistance / GetBlackboard()->GetPinPullMaxDistance();
		Color previewColor = Color::Lerp(Colors::DarkGreen, Colors::SoftGreen, dragT);
		GameRenderManager::GetInstance()->DrawGizmoLine(previewColor, Line<float>(m_pinPosition, hit.point));
	}
}
