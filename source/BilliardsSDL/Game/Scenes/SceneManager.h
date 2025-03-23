#pragma once
#include "SceneName.h"


class SceneManager
{
public:
	SceneManager();
	~SceneManager();


	void LoadScene(const SceneName sceneName);

};