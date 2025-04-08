#pragma once

#include "../../GameObjects/GameObject.h"
#include "../../GameObjects/Behaviours/Testers/AABoxColliderDrawer.h"
#include "../../GameObjects/Behaviours/Testers/CircleColliderDrawer.h"

#include "../../Systems/GameTime.h"
#include "../../Systems/GameAssetResources.h"
#include "../../Systems/GameRandom.h"
#include "../../Systems/GameTweener.h"

#include "../../Render/GameRenderManager.h"
#include "../../Render/Renderers/Image/Image.h"
#include "../../Render/Renderers/Text/Text.h"

#include "../../UI/UICaster.h"
#include "../../UI/Selectables/Button/UIButton.h"

#include "../../../Shared/Types/Color/Color.h"

#include "../../Physics/Physics2DManager.h"
#include "../../Physics/Colliders/CircleCollider2D.h"
#include "../../Physics/Colliders/AABoxCollider2D.h"
#include "../../Physics/Rigidbodies/Rigidbody2D.h"



class SceneCreateUtilities
{
public:
	SceneCreateUtilities(std::vector<GameObject>* sceneGameObjects);


	GameObject* CreateGameObject(const Vector2<float>& position, const std::string& name);

	std::shared_ptr<Image> CreateImageComponent(GameObject* owner, 
		const ImageResourceData& resourceData);
	std::shared_ptr<Text> CreateTextComponent(GameObject* owner, 
		const TextResourceData& resourceData, const std::string& textString, const int pointSize);

	std::shared_ptr<Rigidbody2D> CreateRigidbodyComponent(GameObject* owner,
		const std::shared_ptr<PhysicMaterial>& physicMaterial, const float& mass, const float& gravityScale);
	std::shared_ptr<CircleCollider2D> CreateCircleColliderComponent(GameObject* owner, 
		Rigidbody2D* optionalRigidbody, const bool& isTrigger, const float& radius);
	std::shared_ptr<AABoxCollider2D> CreateAABoxColliderComponent(GameObject* owner, 
		Rigidbody2D* optionalRigidbody, const bool& isTrigger, const Vector2<float>& size);


	GameObject* CreateInvisibleWall(const Vector2<float>& position, const Vector2<float>& size);


private:
	std::vector<GameObject>* m_sceneGameObjects;
};