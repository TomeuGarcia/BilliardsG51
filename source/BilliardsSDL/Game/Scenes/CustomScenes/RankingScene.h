#pragma once
#include "../Scene.h"
#include "../../Systems/GameInput.h"
#include "../SceneManager.h"

#include "../../GameObjects/Behaviours/Ranking/RankingManager.h"



class RankingScene : public Scene
{
protected:
	void CreateGameObjects() override;
	void DoStart() override;
	void DoUpdate() override;
};