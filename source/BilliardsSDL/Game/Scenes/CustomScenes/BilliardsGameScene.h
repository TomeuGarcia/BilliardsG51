#pragma once
#include <array>
#include "../Scene.h"
#include "../../GameObjects/Behaviours/Billiards/BilliardBall.h"
#include "../../GameObjects/Behaviours/Debug/AABoxColliderDrawer.h"
#include "../../GameObjects/Behaviours/Debug/CircleColliderDrawer.h"
#include "../../Systems/GameInput.h"
#include "../SceneManager.h"


class BilliardsGameScene : public Scene
{
protected:
	virtual void CreateGameObjects() override;
	virtual void DoStart() override;
	virtual void DoUpdate() override;

private:
	BilliardBall* CreateBilliardBall(const Vector2<float>& position, const ImageResourceData& imageData, const int& number);
	
	void CreateBoardWalls(const Vector2<float>& boardCenter);
	GameObject* CreateInvisibleWall(const Vector2<float>& position, const Vector2<float>& size);

	void CreateBoardHoles(const Vector2<float>& boardCenter);
	GameObject* CreateBoardHole(const Vector2<float>& position, const float& radius, const std::string& holeName);


	const std::array<Vector2<float>, 16> SortBallsAndComputeArrangePositions(std::array<BilliardBall*, 16>& balls,
					const Vector2<float> boardCenterPosition, const int& whiteBallIndex, const int& blackBallIndex);
};