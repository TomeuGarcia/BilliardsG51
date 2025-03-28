#include "PlayerThinkingState_Hitting.h"


PlayerThinkingState_Hitting::PlayerThinkingState_Hitting(BilliardsGameplayStateBlackboard* blackboard, BilliardsPlayer* player)
	: PlayerThinkingState(blackboard, player), m_tweenWaitTimer(0.0f)
{
}

void PlayerThinkingState_Hitting::DoEnter()
{
	float tweenDuration;
	GetPlayer()->GetStick()->TweenTipToPosition(GetBlackboard()->p_pinPosition, tweenDuration);
	m_tweenWaitTimer.SetDuration(tweenDuration);
	m_tweenWaitTimer.ClearTime();
}

bool PlayerThinkingState_Hitting::Update()
{
	m_tweenWaitTimer.Update(GameTime::GetInstance()->GetDeltaTime());
	if (m_tweenWaitTimer.HasFinished())
	{
		if (TryHitBalls())
		{
			SetNextState(Type::Finished);
		}
		else
		{
			SetNextState(Type::MovingAround);
		}
		return true;
	}

	return false;
}

void PlayerThinkingState_Hitting::Exit()
{
	GetPlayer()->GetStick()->SetResting();
}



bool PlayerThinkingState_Hitting::TryHitBalls()
{
	const Vector2<float> hitPosition = GetBlackboard()->p_pinPosition;
	const Vector2<float> hitDirection = GetBlackboard()->p_directionToPinPosition;
	const float forceMagnitude = GetBlackboard()->p_pinPullDistanceForHit * GetBlackboard()->GetStickForceOverDistanceMultiplier();

	return GetBlackboard()->GetSpecialEventsManager()->TryHitBalls(hitPosition, hitDirection, forceMagnitude);
}
