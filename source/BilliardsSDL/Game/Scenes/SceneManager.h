#pragma once
#include "../../Shared/Types/Color/Color.h"
#include "SceneName.h"
#include "CustomScenes/EmptyScene.h"


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
	Scene* GetActiveScene() const;


public:
	void LoadScene(const SceneName sceneName);	


private:
	Scene* MakeNewSceneByName(const SceneName sceneName);
	void InitNewActiveScene(Scene* newScene);
	void CleanupActiveScene();


private:
	Scene* m_activeScene;

private:
	static SceneManager* s_sceneManager;
};