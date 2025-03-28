#pragma once
#include "ResolvingBoardState.h"


class ResolvingBoardState_ReturningMissplacedBalls : public ResolvingBoardState
{
public:
	ResolvingBoardState_ReturningMissplacedBalls(BilliardsGameplayStateBlackboard* blackboard);
	~ResolvingBoardState_ReturningMissplacedBalls();


	bool Update() override;
	void Exit() override;

protected:
	void DoEnter() override;

private:
	void RepositionCurrentBall();


private:
	bool m_playerkeepsPlaying;

	const std::vector<BilliardBall*>* m_missplacedBalls;

	size_t m_missplacedBallsI;

	Timer m_repositionMissplacedBallTimer;
};

