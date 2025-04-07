#pragma once
#include "../../Shared/Types/Color/Color.h"
#include "SceneName.h"
#include "CustomScenes/EmptyScene.h"
#include "CustomScenes/BilliardsGameScene.h"
#include "CustomScenes/MainMenuScene.h"


class SceneManager
{
public:
	SceneManager();
	~SceneManager();

public:
	static SceneManager* GetInstance();

public:
	void Init(const SceneName startingSceneName);
	void Cleanup();
	void UpdateLoading();
	Scene* GetActiveScene() const;


public:
	void LoadScene(const SceneName sceneName);	


private:
	void LoadQueuedScene();	
	void DoLoadScene(const SceneName sceneName);	
	Scene* MakeNewSceneByName(const SceneName sceneName);
	void InitNewActiveScene(Scene* newScene);
	void CleanupActiveScene();


private:
	bool m_queuedLoadScene;
	SceneName m_queuedLoadSceneName;
	Scene* m_activeScene;

private:
	static SceneManager* s_sceneManager;
};