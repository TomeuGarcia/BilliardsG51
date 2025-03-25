#pragma once
#include <array>
#include "../Scene.h"
#include "../../GameObjects/Behaviours/Billiards/BilliardBall.h"


class BilliardsGameScene : public Scene
{
protected:
	virtual void CreateGameObjects() override;
	virtual void DoStart() override;

private:
	BilliardBall* CreateBilliardBall(const Vector2<float>& position, const ImageResourceData& imageData);

	const std::array<Vector2<float>, 16> SortBallsAndComputeArrangePositions(std::array<BilliardBall*, 16>& balls,
					const Vector2<float> boardCenterPosition, const int& whiteBallIndex, const int& blackBallIndex);
};