#include "RankingScene.h"


void RankingScene::CreateGameObjects()
{
	RankingManager rankingManager{};
	rankingManager.Load();

	std::vector<RankingEntry> entries = rankingManager.GetFilledRankingEntries();
	for (int i = 0; i < entries.size(); ++i)
	{
		const Vector2<float> position = { 0.0f, 1.4f - (i * 0.4f) };

		GetPrefabUtilities().CreateRankingEntryDisplay(position, entries[i], i);
	}
}

void RankingScene::DoStart()
{
	GameRenderManager::GetInstance()->SetBackgroundColor(Colors::DarkPurple);
}

void RankingScene::DoUpdate()
{
	if (GameInput::GetInstance()->GetKeyDown(KeyCode::Esc))
	{
		SceneManager::GetInstance()->LoadScene(SceneName::MainMenu);
	}
	
	if (GameInput::GetInstance()->GetKeyDown(KeyCode::R))
	{
		RankingManager rankingManager{};
		rankingManager.ClearEntries();
		rankingManager.Save();
	}
}
