#include "PlayerThinkingState_Starting.h"

PlayerThinkingState_Starting::PlayerThinkingState_Starting(BilliardsGameplayStateBlackboard* blackboard, BilliardsPlayer* player)
	: PlayerThinkingState(blackboard, player), m_transitionTimer(0.5f), m_startingColor()
{}


void PlayerThinkingState_Starting::DoEnter()
{
	m_transitionTimer.ClearTime();
	m_startingColor = GameRenderManager::GetInstance()->GetBackgroundColor();

	GetBlackboard()->SetCurrentPlayer(GetPlayer());
}

bool PlayerThinkingState_Starting::Update()
{
	m_transitionTimer.Update(GameTime::GetInstance()->GetDeltaTime());

	Color backgroundColor = Color::Lerp(m_startingColor, GetPlayer()->GetBackgroundColor(), m_transitionTimer.GetRatio01());
	GameRenderManager::GetInstance()->SetBackgroundColor(backgroundColor);


	if (m_transitionTimer.HasFinished())
	{
		SetNextState(Type::MovingAround);
		return true;
	}

	return false;
}

void PlayerThinkingState_Starting::Exit()
{

}