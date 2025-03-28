#pragma once
#include "../../Player/BilliardsPlayer.h"


class PlayerThinkingState
{
public:
	enum class Type
	{
		None,

		MovingAround,
		PinnedToHit,
		Hitting,

		Finished
	};


public:
	PlayerThinkingState(BilliardsPlayer* player);

	void Enter();
	virtual bool Update() = 0;
	virtual void Exit() = 0;

	Type GetNextState() const;


protected:
	virtual void DoEnter() = 0;
	void SetNextState(const Type& nextState);

	BilliardsPlayer* GetPlayer() const;


private:
	Type m_nextState;
	BilliardsPlayer* m_player;
};


