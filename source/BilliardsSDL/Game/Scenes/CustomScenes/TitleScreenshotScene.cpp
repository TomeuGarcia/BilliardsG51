#include "TitleScreenshotScene.h"

void TitleScreenshotScene::CreateGameObjects()
{
	const Vector2<float> boardPosition{ 0.0f, 0.0f };
	std::shared_ptr<MainMenuBilliardsBoardManager> boardManager = std::make_shared<MainMenuBilliardsBoardManager>();
	GetPrefabUtilities().CreateBilliardsBoard(boardPosition, boardManager.get());

	const Vector2<float> randomBounds{ 5.0f, 2.0f };
	std::vector<BilliardBall*> balls = GetPrefabUtilities().CreateBilliardsGameBalls(boardManager.get());
	for (auto it = balls.begin(); it != balls.end(); ++it)
	{
		BilliardBall* ball = *it;
		do
		{
			Vector2<float> position = GamePhysicsUtilities::FindRandomPositionWithoutObstacles(boardPosition, randomBounds, 0.2f, 5);
			ball->SetPosition(position);
		} while (Math::Abs(ball->GetTransform()->p_worldPosition.y + boardPosition.y) < 0.7f);
	}


	TrippyText::Config trippyTitleConfig
	{
		88,
		&(GameAssetResources::GetInstance()->GetText().titleTextFontData),

		6,
		0.25f,

		1.6f,
		2.5f,

		Colors::White,
		Colors::DarkGrey,
		Colors::SoftRed,
		Colors::SoftBlue
	};

	TrippyText* trippyTitle = GetPrefabUtilities().CreateTrippyText(Vector2<float>(0.0f, 0.0f), trippyTitleConfig, "A Billiards Game");

	GameObject* managerGameObject = GetCreateUtilities().CreateGameObject(Vector2<float>::Zero(), "Manager");
	std::shared_ptr<TitleScreenshotManager> titleScreenshotManager = std::make_shared<TitleScreenshotManager>(boardManager);
	managerGameObject->AttachBehaviour(titleScreenshotManager);
}

void TitleScreenshotScene::DoStart()
{
	GameRenderManager::GetInstance()->SetBackgroundColor(Colors::DarkPurple);
	AABoxColliderDrawer::s_enabled = false;
	CircleColliderDrawer::s_enabled = false;
}

void TitleScreenshotScene::DoUpdate()
{
	if (GameInput::GetInstance()->GetKeyDown(KeyCode::Space))
	{
		SceneManager::GetInstance()->LoadScene(SceneName::MainMenu);
	}
}
