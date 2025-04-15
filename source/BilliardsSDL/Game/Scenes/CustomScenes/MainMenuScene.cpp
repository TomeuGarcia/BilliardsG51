#include "MainMenuScene.h"

void MainMenuScene::CreateGameObjects()
{
	const Vector2<float> boardPosition{ 0.0f, -0.6f };
	std::shared_ptr<MainMenuBilliardsBoardManager> boardManager = std::make_shared<MainMenuBilliardsBoardManager>();
	GetPrefabUtilities().CreateBilliardsBoard(boardPosition, boardManager.get());

	const Vector2<float> randomBounds{ 5.0f, 2.0f };
	std::vector<BilliardBall*> balls = GetPrefabUtilities().CreateBilliardsGameBalls(nullptr);
	for (auto it = balls.begin(); it != balls.end(); ++it)
	{
		BilliardBall* ball = *it;
		do
		{
			Vector2<float> position = GamePhysicsUtilities::FindRandomPositionWithoutObstacles(boardPosition, randomBounds, 0.2f, 5);
			ball->SetPosition(position);
		} 
		while (Math::Abs(ball->GetTransform()->p_worldPosition.x + boardPosition.x) < 1.0f);
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

	TrippyText* trippyTitle = GetPrefabUtilities().CreateTrippyText(Vector2<float>(0.0f, 3.0f), trippyTitleConfig, "A Billiards Game");


	MenuButton* playButton = GetPrefabUtilities().CreateDefaultMenuButton(Vector2<float>(0.0f, 0.5f), true,
		GameAssetResources::GetInstance()->GetText().defaultTextFontData, "Play", 36, GameAssetResources::GetInstance()->GetAudio().buttonOkSoundData);	
	
	MenuButton* rankingButton = GetPrefabUtilities().CreateDefaultMenuButton(Vector2<float>(0.0f, -0.25f), true,
		GameAssetResources::GetInstance()->GetText().defaultTextFontData, "Ranking", 36, GameAssetResources::GetInstance()->GetAudio().buttonOkSoundData);

	MenuButton* optionsButton = GetPrefabUtilities().CreateDefaultMenuButton(Vector2<float>(0.0f, -1.0f), false,
		GameAssetResources::GetInstance()->GetText().defaultTextFontData, "Options", 36, GameAssetResources::GetInstance()->GetAudio().buttonOkSoundData);

	MenuButton* quitButton = GetPrefabUtilities().CreateDefaultMenuButton(Vector2<float>(0.0f, -1.75f), true,
		GameAssetResources::GetInstance()->GetText().defaultTextFontData, "Quit", 36, GameAssetResources::GetInstance()->GetAudio().buttonBackSoundData);


	
	OptionsMenu* optionsMenu = GetPrefabUtilities().CreateOptionsMenu();

	GameObjectGroup objectsToHideWhenOptionsShown{5};
	//objectsToHideWhenOptionsShown.Add(titleGameObject);
	objectsToHideWhenOptionsShown.Add(trippyTitle->GetGameObjects());
	objectsToHideWhenOptionsShown.Add(playButton->GetGameObject());
	objectsToHideWhenOptionsShown.Add(rankingButton->GetGameObject());
	objectsToHideWhenOptionsShown.Add(optionsButton->GetGameObject());
	objectsToHideWhenOptionsShown.Add(quitButton->GetGameObject());


	GameObject* managerGameObject = GetCreateUtilities().CreateGameObject(Vector2<float>::Zero(), "Manager");
	std::shared_ptr<MainMenuManager> mainMenuManager = std::make_shared<MainMenuManager>(
		boardManager,
		playButton, rankingButton, optionsButton, quitButton,
		optionsMenu, objectsToHideWhenOptionsShown
	);
	managerGameObject->AttachBehaviour(mainMenuManager);



	const GameMusicService::MusicType musicType = GameMusicService::MusicType::MainMenu;
	if (!GameMusicService::GetInstance()->IsMusicPlaying(musicType))
	{
		GetPrefabUtilities().CreatePlayingMusicText(Vector2<float>(-5.5f, -3.5f), musicType);
	}
}



void MainMenuScene::DoStart()
{
	GameRenderManager::GetInstance()->SetBackgroundColor(Colors::DarkPurple);
	GameMusicService::GetInstance()->TransitionMusic(GameMusicService::MusicType::MainMenu);

	AABoxColliderDrawer::s_enabled = false;
	CircleColliderDrawer::s_enabled = false;
}

void MainMenuScene::DoUpdate()
{

}
