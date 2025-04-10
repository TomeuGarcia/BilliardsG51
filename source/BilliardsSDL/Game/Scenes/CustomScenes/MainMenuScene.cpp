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

	UIButton* quitButton = GetPrefabUtilities().CreateDefaultButton(Vector2<float>(-5.0f, 1.25f),
		GameAssetResources::GetInstance()->GetDebugTextFontData(), "Quit", 36);
	quitButton->p_onSelectedCallback = []() { GameAppInteractions::GetInstance()->Quit(); };
	

	UIButton* playButton = GetPrefabUtilities().CreateDefaultButton(Vector2<float>(0.0f, 1.25f),
		GameAssetResources::GetInstance()->GetDebugTextFontData(), "Play", 36);
	playButton->p_onSelectedCallback = []() { 
		SceneManager::GetInstance()->LoadScene(SceneName::BilliardGame);
		};
	

	UIButton* rankingButton = GetPrefabUtilities().CreateDefaultButton(Vector2<float>(5.0f, 1.25f),
		GameAssetResources::GetInstance()->GetDebugTextFontData(), "Ranking", 36);
	rankingButton->p_onSelectedCallback = []() { SceneManager::GetInstance()->LoadScene(SceneName::Ranking); };


	GameObject* titleGameObject = GetCreateUtilities().CreateGameObject(Vector2<float>(0.0f, 3.0f), "Title");
	GetCreateUtilities().CreateTextComponent(titleGameObject, GameAssetResources::GetInstance()->GetDebugTextFontData(), "Billiards G51", 48);
}



void MainMenuScene::DoStart()
{
	GameRenderManager::GetInstance()->SetBackgroundColor(Colors::DarkPurple);

	AABoxColliderDrawer::s_enabled = false;
	CircleColliderDrawer::s_enabled = false;

	sound = GameAudioManager::GetInstance()->CreateSFXSound(GameAssetResources::GetInstance()->GetButtonPressedSoundData());
	sound->Play();
}

void MainMenuScene::DoUpdate()
{

}
