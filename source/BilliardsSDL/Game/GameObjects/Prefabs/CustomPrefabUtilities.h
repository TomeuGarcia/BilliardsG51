#pragma once
#include "../../Scenes/Utilities/SceneCreateUtilities.h"

#include "../../GameObjects/Behaviours/Billiards/BilliardBall.h"
#include "../../GameObjects/Behaviours/Billiards/BilliardStick.h"
#include "../../GameObjects/Behaviours/Billiards/Holes/BilliardsBoardHole.h"


class CustomPrefabUtilities
{
public:
	CustomPrefabUtilities(SceneCreateUtilities* sceneCreateUtilities);

public:
	BilliardBall* CreateBilliardsBall(const Vector2<float>& position, const ImageResourceData& imageData,
		const BilliardBall::ColorType& colorType, const int& number);
	std::vector<BilliardBall*> CreateBilliardsGameBalls();

	
	BilliardStick* CreateBilliardsStick(const Vector2<float>& position, const ImageResourceData& imageData, const std::string& name);


	GameObject* CreateBilliardsBoard(const Vector2<float>& position, IBilliardBoardHoleInteractionsManager* holeInteractionManager);
	void CreateBoardWalls(const Vector2<float>& boardCenter);
	void CreateBoardHoles(const Vector2<float>& boardCenter, IBilliardBoardHoleInteractionsManager* holeInteractionManager);
	GameObject* CreateBoardHole(const Vector2<float>& position, const float& radius, const std::string& holeName,
		IBilliardBoardHoleInteractionsManager* holeInteractionManager);

private:
	SceneCreateUtilities* m_sceneCreateUtilities;
};