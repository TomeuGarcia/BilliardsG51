#include "MainMenuScene.h"

void MainMenuScene::CreateGameObjects()
{
	/*
	const Vector2<float> ballBounds{6.0f, 4.0f};
	for (int i = 0; i < 40; ++i)
	{
		const Vector2<float> position = GameRandom::GetInstance()->GetRandomVectorBetweenSignedBounds(ballBounds);
		const ImageResourceData imageData = GameRandom::GetInstance()->GetRandomBool(0.5f)
			? GameAssetResources::GetInstance()->GetBlueBallImageData()
			: GameAssetResources::GetInstance()->GetRedBallImageData();

		const float scale = GameRandom::GetInstance()->GetRandomFloat(1.0f, 0.5f);
		const Vector2 size = Vector2<float>::One() * scale;


		GameObject* ballGameObject = CreateGameObject(position, std::string("Ball_") + std::to_string(i));
		std::shared_ptr<Image> image = CreateImageComponent(ballGameObject, imageData, size);
		image->SetColorTint(Colors::White * (1.0f - scale));
	}
	*/


	std::shared_ptr<MainMenuBilliardsBoardManager> boardManager = std::make_shared<MainMenuBilliardsBoardManager>();
	GetPrefabUtilities().CreateBilliardsBoard(Vector2<float>(0.0f, -0.6f), boardManager.get());


	/*
	GameObject* holeGameObject = CreateGameObject(Vector2<float>(0.0f, -2.0f), "Hole");
	std::shared_ptr<BilliardsBoardHole> boardHole = std::make_shared<BilliardsBoardHole>(holeGameObject->GetTransform(), );
	holeGameObject->AttachBehaviour(boardHole);
	*/
	

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
