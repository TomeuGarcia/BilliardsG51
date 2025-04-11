#pragma once
#include "../../Scenes/Utilities/SceneCreateUtilities.h"
#include "../GameObjectGroup.h"

#include "../Behaviours/Billiards/BallFeedback/BallCollisionFeedbackManager.h"
#include "../Behaviours/Billiards/BallFeedback/BallCollisionDetector.h"
#include "../Behaviours/Billiards/BilliardBall.h"
#include "../Behaviours/Billiards/BilliardStick.h"
#include "../Behaviours/Billiards/Holes/BilliardsBoardHole.h"

#include "../Behaviours/RendererExtras/FadingRenderer.h"

#include "../Behaviours/Ranking/RankingEntry.h"
#include "../Behaviours/Ranking/RankingEntryDisplay.h"

#include "../Behaviours/CustomUI/MenuButton.h"


class CustomPrefabUtilities
{
public:
	CustomPrefabUtilities(SceneCreateUtilities* sceneCreateUtilities);


public:
	MenuButton* CreateDefaultMenuButton(const Vector2<float>& position,
		const TextResourceData& textData, const std::string& textString, const int pointSize,
		const SoundResourceData& soundData);
	MenuButton* CreateDangerMenuButton(const Vector2<float>& position,
		const TextResourceData& textData, const std::string& textString, const int pointSize);


public:
	BallCollisionFeedbackManager* CreateBallCollisionFeedbackManager();

	BilliardBall* CreateBilliardsBall(const Vector2<float>& position, const ImageResourceData& imageData,
		const BilliardBall::ColorType& colorType, const int& number, BallCollisionFeedbackManager* feedbackManager);
	std::vector<BilliardBall*> CreateBilliardsGameBalls(BallCollisionFeedbackManager* feedbackManager);

	
	BilliardStick* CreateBilliardsStick(const Vector2<float>& position, const ImageResourceData& imageData, const std::string& name);


	GameObject* CreateBilliardsBoard(const Vector2<float>& position, IBilliardBoardHoleInteractionsManager* holeInteractionManager);
	void CreateBoardWalls(const Vector2<float>& boardCenter);
	void CreateBoardHoles(const Vector2<float>& boardCenter, IBilliardBoardHoleInteractionsManager* holeInteractionManager);
	GameObject* CreateBoardHole(const Vector2<float>& position, const float& radius, const std::string& holeName,
		IBilliardBoardHoleInteractionsManager* holeInteractionManager);


public:
	FadingRenderer* CreateBanishingFadingText(const std::string& textString, const Color& color, const bool& big);

	FadingRenderer* CreateOpaqueFadingText(const std::string& textString, const Color& color, const bool& big);


public:
	void CreateRankingEntryDisplay(const Vector2<float>& position, const RankingEntry& rankingEntry, const int& index);


public:
	GameObjectGroup CreateOptionsMenu(const std::string& title, MenuButton* outBackButton);


private:
	SceneCreateUtilities* m_sceneCreateUtilities;
};