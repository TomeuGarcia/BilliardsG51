#pragma once
#include "../../Scenes/Utilities/SceneCreateUtilities.h"

#include "../Behaviours/Billiards/BilliardBall.h"
#include "../Behaviours/Billiards/BilliardStick.h"
#include "../Behaviours/Billiards/Holes/BilliardsBoardHole.h"

#include "../Behaviours/RendererExtras/FadingRenderer.h"

#include "../Behaviours/Ranking/RankingEntry.h"
#include "../Behaviours/Ranking/RankingEntryDisplay.h"


class CustomPrefabUtilities
{
public:
	CustomPrefabUtilities(SceneCreateUtilities* sceneCreateUtilities);


public:
	UIButton* CreateDefaultButton(const Vector2<float>& position,
		const TextResourceData& textData, const std::string& textString, const int pointSize);


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


public:
	FadingRenderer* CreateFadingText(const std::string& textString, const Color& color, const bool& big);


public:
	void CreateRankingEntryDisplay(const Vector2<float>& position, const RankingEntry& rankingEntry, const int& index);



private:
	SceneCreateUtilities* m_sceneCreateUtilities;
};