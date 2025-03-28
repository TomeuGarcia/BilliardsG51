#pragma once
#include "../../Player/BilliardsPlayer.h"

#include "../BilliardsGameplayStateBlackboard.h"
#include "../../../../../Systems/GameTweener.h"
#include "../../../../../Systems/GameTime.h"
#include "../../../../../Systems/GameInput.h"
#include "../../../../../Systems/GameRandom.h"
#include "../../../../../../Shared/Timer/Timer.h"


class PlayerThinkingState
{
public:
	enum class Type
	{
		None,

		Starting,
		MovingAround,
		PinnedToHit,
		Hitting,

		Finished
	};


public:
	PlayerThinkingState(BilliardsGameplayStateBlackboard* blackboard, BilliardsPlayer* player);

	void Enter();
	virtual bool Update() = 0;
	virtual void Exit() = 0;

	Type GetNextState() const;


protected:
	virtual void DoEnter() = 0;
	void SetNextState(const Type& nextState);

	BilliardsGameplayStateBlackboard* GetBlackboard() const;
	BilliardsPlayer* GetPlayer() const;


private:
	Type m_nextState;

	BilliardsGameplayStateBlackboard* m_blackboard;
	BilliardsPlayer* m_player;
};


