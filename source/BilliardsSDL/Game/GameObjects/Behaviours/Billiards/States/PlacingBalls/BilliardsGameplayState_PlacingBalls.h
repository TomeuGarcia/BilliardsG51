#pragma once
#include "../BilliardsGameplayState.h"


class BilliardsGameplayState_PlacingBalls : public BilliardsGameplayState
{
public:
	BilliardsGameplayState_PlacingBalls(BilliardsGameplayStateBlackboard* blackboard);
	virtual ~BilliardsGameplayState_PlacingBalls();


	bool Update() override;
	void Exit() override;

protected:
	void DoEnter() override;


private:
	void SetBallsIgnoringPhysics();
	void SetBallsCheckingPhysics();


	void StartPlacingBalls();

	std::vector<Vector2<float>> ComputeArrangedSortedPositions(const Vector2<float>& boardCenter,
		const std::vector<BilliardBall*>& balls, const int& whiteBallIndex, const int& blackBallIndex);

	void ShuffleBallPositions(std::vector<Vector2<float>>& ballPositions, const Vector2<int>& boundsA, const Vector2<int>& boundsB);

	void MoveBalls(const std::vector<BilliardBall*>& balls, const std::vector<Vector2<float>>& ballPositions);


private:
	Timer m_placingTimer;
};