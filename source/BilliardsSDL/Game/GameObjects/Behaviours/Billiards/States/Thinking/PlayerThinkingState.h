#pragma once


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
	void Enter();
	virtual bool Update() = 0;
	virtual void Exit() = 0;

	Type GetNextState() const;


protected:
	virtual void DoEnter() = 0;
	void SetNextState(const Type& nextState);


private:
	Type m_nextState;
};


