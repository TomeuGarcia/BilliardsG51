#pragma once
#include <vector>

#include "../GameObjects/GameObject.h"
#include "../Systems/GameTime.h"
#include "../Systems/GameAssetResources.h"
#include "../Systems/GameRandom.h"
#include "../Render/GameRenderManager.h"
#include "../Render/Renderers/Image/Image.h"
#include "../Render/Renderers/Text/Text.h"
#include "../../Shared/Types/Color/Color.h"
#include "../Physics/Physics2DManager.h"
#include "../Physics/Colliders/CircleCollider2D.h"
#include "../Physics/Colliders/AABoxCollider2D.h"
#include "../Physics/Rigidbodies/Rigidbody2D.h"


class Scene
{
public:
	Scene();
	~Scene();

	void Init();
	void Cleanup();

	void Start();
	void Update();
	void Render();


protected:
	virtual void CreateGameObjects() = 0;
	GameObject* CreateGameObject(const Vector2<float>& position);
	std::shared_ptr<Image> CreateImageComponent(GameObject* owner, const ImageResourceData& resourceData, const Vector2<float>& size);
	std::shared_ptr<Text> CreateTextComponent(GameObject* owner, const TextResourceData& resourceData,
											  const std::string& textString, const int pointSize);

	std::shared_ptr<Rigidbody2D> CreateRigidbodyComponent(GameObject* gameObject, 
														  const std::shared_ptr<PhysicMaterial>& physicMaterial,
														  const float& mass, const float& gravityScale);
	std::shared_ptr<CircleCollider2D> CreateCircleColliderComponent(GameObject* owner, Rigidbody2D* optionalRigidbody, const float& radius);
	std::shared_ptr<AABoxCollider2D> CreateAABoxColliderComponent(GameObject* owner, Rigidbody2D* optionalRigidbody, const Vector2<float>& size);


	virtual void DoStart() = 0;


private:
	std::vector<GameObject> m_gameObjects;
};