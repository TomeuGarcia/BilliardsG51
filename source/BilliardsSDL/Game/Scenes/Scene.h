#pragma once
#include <vector>
#include <forward_list>

#include "../GameObjects/Prefabs/CustomPrefabUtilities.h"
#include "../Audio/MusicService/GameMusicService.h"
#include "../Systems/GameAppInteractions.h"


class Scene
{
public:
	Scene();
	~Scene();

	void Init();
	void Cleanup();

	void Start();
	void Update();


protected:
	SceneCreateUtilities& GetCreateUtilities();
	CustomPrefabUtilities& GetPrefabUtilities();

	virtual void CreateGameObjects() = 0;
	virtual void DoStart() = 0;
	virtual void DoUpdate() = 0;
	virtual void OnDestroy();

private:
	SteppingBuffer<GameObject> m_gameObjectsBuffer;

	SceneCreateUtilities m_createUtilities;
	CustomPrefabUtilities m_customPrefabs;
};