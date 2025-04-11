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



	GameObject* managerGameObject = GetCreateUtilities().CreateGameObject(Vector2<float>::Zero(), "Manager");
	std::shared_ptr<MainMenuManager> mainMenuManager = std::make_shared<MainMenuManager>();
	managerGameObject->AttachBehaviour(mainMenuManager);

	GetPrefabUtilities().CreateBilliardsBoard(Vector2<float>(0.0f, -2.0f), mainMenuManager.get());


	/*
	GameObject* holeGameObject = CreateGameObject(Vector2<float>(0.0f, -2.0f), "Hole");
	std::shared_ptr<BilliardsBoardHole> boardHole = std::make_shared<BilliardsBoardHole>(holeGameObject->GetTransform(), );
	holeGameObject->AttachBehaviour(boardHole);
	*/

	MenuButton* quitButton = GetPrefabUtilities().CreateDefaultMenuButton(Vector2<float>(-5.0f, 1.25f),
		GameAssetResources::GetInstance()->GetText().debugTextFontData, "Quit", 36, GameAssetResources::GetInstance()->GetAudio().buttonBackSoundData);
	quitButton->SetSelectedCallback([]() { GameAppInteractions::GetInstance()->Quit(); });
	

	MenuButton* playButton = GetPrefabUtilities().CreateDefaultMenuButton(Vector2<float>(0.0f, 1.25f),
		GameAssetResources::GetInstance()->GetText().debugTextFontData, "Play", 36, GameAssetResources::GetInstance()->GetAudio().buttonOkSoundData);
	playButton->SetSelectedCallback([]() { SceneManager::GetInstance()->LoadScene(SceneName::BilliardGame);	});
	

	MenuButton* rankingButton = GetPrefabUtilities().CreateDefaultMenuButton(Vector2<float>(5.0f, 1.25f),
		GameAssetResources::GetInstance()->GetText().debugTextFontData, "Ranking", 36, GameAssetResources::GetInstance()->GetAudio().buttonOkSoundData);
	rankingButton->SetSelectedCallback([]() { SceneManager::GetInstance()->LoadScene(SceneName::Ranking); });


	GameObject* titleGameObject = GetCreateUtilities().CreateGameObject(Vector2<float>(0.0f, 3.0f), "Title");
	GetCreateUtilities().CreateTextComponent(titleGameObject, GameAssetResources::GetInstance()->GetText().debugTextFontData, "Billiards G51", 48);



	MenuIncDecButton::Config incDecConfig{
		0,
		100,
		10,		
		28,
		36,
		36,
		ColorBlock{Colors::LightPurple, Colors::SoftYellow, Colors::SoftGreen},
		ColorBlock{Colors::LightPurple, Colors::SoftYellow, Colors::SoftRed},
		&GameAssetResources::GetInstance()->GetAudio().buttonOkSoundData,
		&GameAssetResources::GetInstance()->GetAudio().buttonBackSoundData,
		&GameAssetResources::GetInstance()->GetText().debugTextFontData,
		Colors::White
	};

	GameObject* masterVolumeGameObject = GetCreateUtilities().CreateGameObject(Vector2<float>(0.0f, 0.0f), "MasterVolume");
	std::shared_ptr<MenuIncDecButton> masterVolumeIncDec = std::make_shared<MenuIncDecButton>(&GetCreateUtilities(), 
		incDecConfig, "Master Volume", 100, masterVolumeGameObject);
	masterVolumeGameObject->AttachBehaviour(masterVolumeIncDec);

	GameObject* musicVolumeGameObject = GetCreateUtilities().CreateGameObject(Vector2<float>(0.0f, -1.0f), "Music");
	std::shared_ptr<MenuIncDecButton> musicVolumeIncDec = std::make_shared<MenuIncDecButton>(&GetCreateUtilities(), 
		incDecConfig, "Music Volume", 50, musicVolumeGameObject);
	musicVolumeGameObject->AttachBehaviour(musicVolumeIncDec);

	GameObject* sfxVolumeGameObject = GetCreateUtilities().CreateGameObject(Vector2<float>(0.0f, -2.0f), "SFX");
	std::shared_ptr<MenuIncDecButton> sfxVolumeIncDec = std::make_shared<MenuIncDecButton>(&GetCreateUtilities(), 
		incDecConfig, "SFX Volume", 50, sfxVolumeGameObject);
	sfxVolumeGameObject->AttachBehaviour(sfxVolumeIncDec);

	/*
	m_options = GetPrefabUtilities().CreateOptionsMenu("Options", m_optionsBack);

	m_optionsBack->SetSelectedCallback([](){ m_options. })
	*/
}



void MainMenuScene::DoStart()
{
	GameRenderManager::GetInstance()->SetBackgroundColor(Colors::DarkPurple);

	AABoxColliderDrawer::s_enabled = false;
	CircleColliderDrawer::s_enabled = false;
}

void MainMenuScene::DoUpdate()
{

}
