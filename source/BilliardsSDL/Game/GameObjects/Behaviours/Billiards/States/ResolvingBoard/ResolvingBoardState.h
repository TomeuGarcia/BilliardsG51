#pragma once
#include "../BilliardsGameplayStateBlackboard.h"
#include "../../../../../Systems/GameTweener.h"
#include "../../../../../Systems/GameTime.h"
#include "../../../../../Systems/GameInput.h"
#include "../../../../../Systems/GameRandom.h"
#include "../../../../../../Shared/Timer/Timer.h"


class ResolvingBoardState
{
public:
	enum class Type
	{
		None,

		WaitingBallsStop,
		ReturningMissplacedBalls,

		ChangePlayer,
		KeepPlayer,

		PlayerVictory
	};


public:
	ResolvingBoardState(BilliardsGameplayStateBlackboard* blackboard);

	void Enter();
	virtual bool Update() = 0;
	virtual void Exit() = 0;

	Type GetNextState() const;


protected:
	virtual void DoEnter() = 0;
	void SetNextState(const Type& nextState);

	BilliardsGameplayStateBlackboard* GetBlackboard() const;


private:
	Type m_nextState;

	BilliardsGameplayStateBlackboard* m_blackboard;
};


