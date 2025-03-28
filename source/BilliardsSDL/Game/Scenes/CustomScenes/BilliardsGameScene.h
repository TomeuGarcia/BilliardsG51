#pragma once
#include <array>
#include "../Scene.h"
#include "../../GameObjects/Behaviours/Debug/AABoxColliderDrawer.h"
#include "../../GameObjects/Behaviours/Debug/CircleColliderDrawer.h"
#include "../../Systems/GameInput.h"

#include "../../GameObjects/Behaviours/Billiards/BilliardBall.h"
#include "../../GameObjects/Behaviours/Billiards/BilliardStick.h"
#include "../../GameObjects/Behaviours/Billiards/BilliardsGameplayManager.h"
#include "../../GameObjects/Behaviours/Billiards/Holes/BilliardsBoardHole.h"



class BilliardsGameScene : public Scene
{
protected:
	virtual void CreateGameObjects() override;
	virtual void DoStart() override;
	virtual void DoUpdate() override;

private:
	BilliardStick* CreateBilliardStick(const Vector2<float>& position, const ImageResourceData& imageData, const std::string& name);


	std::vector<BilliardBall*> CreateBilliardBalls();
	BilliardBall* CreateBilliardBall(const Vector2<float>& position, const ImageResourceData& imageData, 
		const BilliardBall::ColorType& colorType, const int& number);
	

	void CreateBoardWalls(const Vector2<float>& boardCenter);
	GameObject* CreateInvisibleWall(const Vector2<float>& position, const Vector2<float>& size);


	void CreateBoardHoles(const Vector2<float>& boardCenter, IBilliardBoardHoleInteractionsManager* holeInteractionManager);
	GameObject* CreateBoardHole(const Vector2<float>& position, const float& radius, const std::string& holeName,
		IBilliardBoardHoleInteractionsManager* holeInteractionManager);
};