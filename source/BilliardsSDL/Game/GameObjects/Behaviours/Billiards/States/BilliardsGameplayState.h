#pragma once
#include <algorithm>
#include "BilliardsGameplayStateBlackboard.h"
#include "../../../../Systems/GameTweener.h"
#include "../../../../Systems/GameTime.h"
#include "../../../../Systems/GameInput.h"
#include "../../../../Systems/GameRandom.h"
#include "../../../../../Shared/Timer/Timer.h"


class BilliardsGameplayState
{
public:
	enum class Type
	{
		None,

		Init,
		PlacingBalls,
		Thinking_Red,
		Thinking_Blue,
		ResolvingBoard,
		GameFinish,

		GameQuit
	};


public:
	BilliardsGameplayState(BilliardsGameplayStateBlackboard* blackboard);
	virtual ~BilliardsGameplayState();

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