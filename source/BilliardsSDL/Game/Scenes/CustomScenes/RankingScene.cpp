#include "RankingScene.h"


void RankingScene::CreateGameObjects()
{
	CreateBackgroundGameObject();
	CreateRankingGameObject();
}

void RankingScene::DoStart()
{
	GameRenderManager::GetInstance()->SetBackgroundColor(Colors::DarkPurple);
}

void RankingScene::DoUpdate()
{
	if (GameInput::GetInstance()->GetKeyDown(KeyCode::R))
	{
		RankingManager rankingManager{};
		rankingManager.ClearEntries();
		rankingManager.Save();
	}
}



void RankingScene::CreateBackgroundGameObject()
{
	ParallaxBallsBackground::Config backgroundConfig
	{
		30,

		Vector2<float>{ 7.0f, 4.0f },
		4.5f,

		0.8f,
		0.4f,
		8,

		0.8f,
		0.3f
	};


	GameObject* backgroundGameObject = GetCreateUtilities().CreateGameObject(Vector2<float>::Zero(), "Background");
	std::shared_ptr<ParallaxBallsBackground> parallaxBallsBackground = std::make_shared<ParallaxBallsBackground>(
		backgroundConfig, &GetCreateUtilities());
	backgroundGameObject->AttachBehaviour(parallaxBallsBackground);
}



void RankingScene::CreateRankingGameObject()
{
	RankingManager rankingManager{};
	rankingManager.Load();

	const float startY = 1.8f;
	const float spacingY = 0.5f;

	std::vector<RankingEntry> entries = rankingManager.GetFilledRankingEntries();
	const int occuppiedEntriesSize = entries.size();
	for (int i = 0; i < occuppiedEntriesSize; ++i)
	{
		const Vector2<float> position = { 0.0f, startY - (i * spacingY) };
		GetPrefabUtilities().CreateRankingEntryDisplay(position, entries[i], i);
	}

	entries = rankingManager.GetRemainingEmptyRankingEntries();
	for (int i = 0; i < entries.size(); ++i)
	{
		const int index = i + occuppiedEntriesSize;
		const Vector2<float> position = { 0.0f, startY - (index * spacingY) };
		GetPrefabUtilities().CreateRankingEntryDisplay(position, entries[i], index);
	}



	MenuButton* backToMenuButton = GetPrefabUtilities().CreateDefaultMenuButton(Vector2<float>(-6.0f, -3.25f), true,
		GameAssetResources::GetInstance()->GetText().defaultTextFontData, "Back", 36, GameAssetResources::GetInstance()->GetAudio().buttonBackSoundData);
	backToMenuButton->SetSelectedCallback([]() { SceneManager::GetInstance()->LoadScene(SceneName::MainMenu); });


	MenuButton* clearRankingButton = GetPrefabUtilities().CreateDangerMenuButton(Vector2<float>(5.3f, -3.35f), true,
		GameAssetResources::GetInstance()->GetText().defaultTextFontData, "Clear Ranking", 25);
	clearRankingButton->SetSelectedCallback([]()
		{
			RankingManager rankingManager{};
			rankingManager.ClearEntries();
			rankingManager.Save();
			SceneManager::GetInstance()->LoadScene(SceneName::Ranking);
		});


	GameObject* titleGameObject = GetCreateUtilities().CreateGameObject(Vector2<float>(0.0f, 2.75f), "Title");
	GetCreateUtilities().CreateTextComponent(titleGameObject, GameAssetResources::GetInstance()->GetText().defaultTextFontData, "-  Ranking  -", 64);
}
