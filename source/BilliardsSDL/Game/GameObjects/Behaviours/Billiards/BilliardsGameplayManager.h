#pragma once
#include <algorithm>

#include "../Behaviour.h"
#include "BilliardBall.h"
#include "BilliardStick.h"

#include "../../../Systems/GameInput.h"

#include "States/Init/BilliardsGameplayState_Init.h"
#include "States/PlacingBalls/BilliardsGameplayState_PlacingBalls.h"
#include "States/Thinking/BilliardsGameplayState_PlayerThinking.h"
#include "States/ResolvingBoard/BilliardsGameplayState_ResolvingBoard.h"
#include "States/GameFinish/BilliardsGameplayState_GameFinish.h"




class BilliardsGameplayManager : public Behaviour
{
public:
	BilliardsGameplayManager();
	~BilliardsGameplayManager();

	void Init(const std::vector<BilliardBall*>& balls, const Vector2<float>& boardCenter,
		BilliardStick* redStick, BilliardStick* blueStick);

	virtual void Update() override;


private:
	BilliardStick* m_stick;

	Vector2<float> m_pinPosition;
	bool m_pinned;



	std::unordered_map<BilliardsGameplayState::Type, std::shared_ptr<BilliardsGameplayState>> m_gameplayStatesMap;
	BilliardsGameplayState* m_currentState;
	BilliardsGameplayStateBlackboard m_gameplayStatesBlackboard;

	BilliardsPlayer m_playerRed;
	BilliardsPlayer m_playerBlue;
};