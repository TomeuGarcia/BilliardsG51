#include "RankingScene.h"


void RankingScene::CreateGameObjects()
{
	RankingManager rankingManager{};
	rankingManager.Load();

	std::vector<RankingEntry> entries = rankingManager.GetFilledRankingEntries();
	const int occuppiedEntriesSize = entries.size();
	for (int i = 0; i < occuppiedEntriesSize; ++i)
	{
		const Vector2<float> position = { 0.0f, 1.4f - (i * 0.4f) };
		GetPrefabUtilities().CreateRankingEntryDisplay(position, entries[i], i);
	}

	entries = rankingManager.GetRemainingEmptyRankingEntries();
	for (int i = 0; i < entries.size(); ++i)
	{
		const int index = i + occuppiedEntriesSize;
		const Vector2<float> position = { 0.0f, 1.4f - (index * 0.4f) };
		GetPrefabUtilities().CreateRankingEntryDisplay(position, entries[i], index);
	}



	UIButton* backToMenuButton = GetPrefabUtilities().CreateDefaultButton(Vector2<float>(-6.0f, -3.25f),
		GameAssetResources::GetInstance()->GetText().debugTextFontData, "Back", 36);
	backToMenuButton->p_onSelectedCallback = []() { SceneManager::GetInstance()->LoadScene(SceneName::MainMenu); };


	UIButton* clearRankingButton = GetPrefabUtilities().CreateDangerButton(Vector2<float>(5.3f, -3.35f),
		GameAssetResources::GetInstance()->GetText().debugTextFontData, "Clear Ranking", 25);
	clearRankingButton->p_onSelectedCallback = []() {
		RankingManager rankingManager{};
		rankingManager.ClearEntries();
		rankingManager.Save();
		SceneManager::GetInstance()->LoadScene(SceneName::Ranking); 
	};


	GameObject* titleGameObject = GetCreateUtilities().CreateGameObject(Vector2<float>(0.0f, 3.0f), "Title");
	GetCreateUtilities().CreateTextComponent(titleGameObject, GameAssetResources::GetInstance()->GetText().debugTextFontData, "-  Ranking  -", 48);
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
