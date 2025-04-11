#include "BilliardsGameScene.h"

void BilliardsGameScene::CreateGameObjects()
{
	BilliardsScore::Configuration scoreConfiguration{ 10, 30, 50, 5 };

	GameObject* managerGameObject = GetCreateUtilities().CreateGameObject(Vector2<float>::Zero(), "Manager");
	std::shared_ptr<BilliardsGameplayManager> manager = std::make_shared<BilliardsGameplayManager>(scoreConfiguration);
	managerGameObject->AttachBehaviour(manager);


	const Vector2<float> boardPosition = Vector2<float>::Zero();
	GetPrefabUtilities().CreateBilliardsBoard(boardPosition, manager.get());

	BallCollisionFeedbackManager* ballCollisionFeedbackManager = GetPrefabUtilities().CreateBallCollisionFeedbackManager();

	std::vector<BilliardBall*> balls = GetPrefabUtilities().CreateBilliardsGameBalls(ballCollisionFeedbackManager);

	BilliardStick* redStick = GetPrefabUtilities().CreateBilliardsStick(boardPosition + Vector2<float>(3, 3),
		GameAssetResources::GetInstance()->GetImage().redStickImageData, "Red stick");
	BilliardStick* blueStick = GetPrefabUtilities().CreateBilliardsStick(boardPosition + Vector2<float>(-3, 3),
		GameAssetResources::GetInstance()->GetImage().blueStickImageData, "Blue stick");





	FadingRenderer* fadingText_whiteBallEnterHole = GetPrefabUtilities().CreateBanishingFadingText("Oops!", Colors::White, false);
	FadingRenderer* fadingText_blackBallEnterHole = GetPrefabUtilities().CreateBanishingFadingText("Oops!", Colors::DarkPurple, false);
	FadingRenderer* fadingText_wrongBallEnterHole = GetPrefabUtilities().CreateBanishingFadingText("Wrong!", Colors::White, false);
	FadingRenderer* fadingText_ballEnterHoleScore = 
		GetPrefabUtilities().CreateBanishingFadingText("+" + std::to_string(scoreConfiguration.p_addValue), Colors::White, true);
	FadingRenderer* fadingText_ballEnterHoleScoreConsecutive = 
		GetPrefabUtilities().CreateBanishingFadingText("+" + std::to_string(scoreConfiguration.p_consecutiveAddValue), Colors::White, true);
	FadingRenderer* fadingText_ballEnterHoleScoreLast = 
		GetPrefabUtilities().CreateBanishingFadingText("+" + std::to_string(scoreConfiguration.p_addLastValue), Colors::White, true);


	FadingRenderer* fadingText_VictoryHeader = GetPrefabUtilities().CreateOpaqueFadingText("Victory", Colors::TransparentWhite, true);
	FadingRenderer* fadingText_VictorySubHeader = GetPrefabUtilities().CreateOpaqueFadingText("Enter winner's name", Colors::TransparentWhite, false);



	std::shared_ptr<ConsolePlayerScoresDisplay> consolePlayerScoresDisplay = std::make_shared<ConsolePlayerScoresDisplay>();
	std::shared_ptr<BilliardsGameplayFeedbackDisplay> gameplayFeedbackisplay = std::make_shared<BilliardsGameplayFeedbackDisplay>(
		BilliardsGameplayFeedbackDisplay::FadingTextsConfig{
			fadingText_whiteBallEnterHole,
			fadingText_blackBallEnterHole,
			fadingText_wrongBallEnterHole,
			fadingText_ballEnterHoleScore,
			fadingText_ballEnterHoleScoreConsecutive,
			fadingText_ballEnterHoleScoreLast,

			fadingText_VictoryHeader,
			fadingText_VictorySubHeader
		},
		BilliardsGameplayFeedbackDisplay::SoundsConfig{
			GameAudioManager::GetInstance(),
			GameAssetResources::GetInstance()->GetAudio().gamePenaltySoundData,
			GameAssetResources::GetInstance()->GetAudio().gameLowPenaltySoundData,
			GameAssetResources::GetInstance()->GetAudio().gameScorePointsSoundData,
			GameAssetResources::GetInstance()->GetAudio().gamePlayerChangeSoundData,
			GameAssetResources::GetInstance()->GetAudio().gameVictorySoundData,
		}
	);

	manager->Init(balls, boardPosition, redStick, blueStick, gameplayFeedbackisplay, consolePlayerScoresDisplay);
}



void BilliardsGameScene::DoStart()
{
	AABoxColliderDrawer::s_enabled = false;
	CircleColliderDrawer::s_enabled = false;
}

void BilliardsGameScene::DoUpdate()
{
	if (GameInput::GetInstance()->GetKeyDown(KeyCode::C))
	{
		AABoxColliderDrawer::s_enabled = !AABoxColliderDrawer::s_enabled;
		CircleColliderDrawer::s_enabled = !CircleColliderDrawer::s_enabled;
	}
}

void BilliardsGameScene::OnDestroy()
{
	AABoxColliderDrawer::s_enabled = false;
	CircleColliderDrawer::s_enabled = false;
}

