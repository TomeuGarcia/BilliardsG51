#pragma once
#include <vector>

#include "../GameObjects/GameObject.h"
#include "../Systems/GameTime.h"
#include "../Systems/GameAssetResources.h"
#include "../Render/GameRenderManager.h"
#include "../Render/Renderers/Image.h"
#include "../../Shared/Types/Color/Color.h"


class Scene
{
public:
	Scene();
	~Scene();

	void Init();
	void Cleanup();

	void Update();
	void Render();


protected:
	virtual void CreateGameObjects() = 0;
	GameObject* CreateGameObject(const Vector2<int>& position);
	std::shared_ptr<Image> CreateImageComponent(GameObject* owner, const ImageResourceData& resourceData, const Vector2<int>& size);


	virtual void Start() = 0;


private:
	std::vector<GameObject> m_gameObjects;
};