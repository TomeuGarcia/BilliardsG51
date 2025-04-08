#include "SceneCreateUtilities.h"

SceneCreateUtilities::SceneCreateUtilities(std::vector<GameObject>* sceneGameObjects)
	: m_sceneGameObjects(sceneGameObjects)
{
}



GameObject* SceneCreateUtilities::CreateGameObject(const Vector2<float>& position, const std::string& name)
{
	return &m_sceneGameObjects->emplace_back(position, name);
}



std::shared_ptr<Image> SceneCreateUtilities::CreateImageComponent(GameObject* owner, 
	const ImageResourceData& resourceData)
{
	std::shared_ptr<Image> image = std::make_shared<Image>(owner, resourceData.p_defaultUnitsSize);
	image->Init(*GameRenderManager::GetInstance(), resourceData);

	GameRenderManager::GetInstance()->AddToRenderQueue(image);

	return image;
}

std::shared_ptr<Text> SceneCreateUtilities::CreateTextComponent(GameObject* owner, 
	const TextResourceData& resourceData, const std::string& textString, const int pointSize)
{
	std::shared_ptr<Text> text = std::make_shared<Text>(owner, textString, pointSize);
	text->Init(*GameRenderManager::GetInstance(), resourceData);

	GameRenderManager::GetInstance()->AddToRenderQueue(text);

	return text;
}



std::shared_ptr<Rigidbody2D> SceneCreateUtilities::CreateRigidbodyComponent(GameObject* owner,
	const std::shared_ptr<PhysicMaterial>& physicMaterial, const float& mass, const float& gravityScale)
{
	std::shared_ptr<Rigidbody2D> rigidbody = std::make_shared<Rigidbody2D>(owner, physicMaterial, mass, gravityScale);
	return rigidbody;
}

std::shared_ptr<CircleCollider2D> SceneCreateUtilities::CreateCircleColliderComponent(GameObject* owner, 
	Rigidbody2D* optionalRigidbody, const bool& isTrigger, const float& radius)
{
	std::shared_ptr<CircleCollider2D> circleCollider = std::make_shared<CircleCollider2D>(owner, optionalRigidbody, isTrigger, radius);
	Physics2DManager::GetInstance()->AddCircleCollider(circleCollider);
	return circleCollider;
}

std::shared_ptr<AABoxCollider2D> SceneCreateUtilities::CreateAABoxColliderComponent(GameObject* owner, 
	Rigidbody2D* optionalRigidbody, const bool& isTrigger, const Vector2<float>& size)
{
	std::shared_ptr<AABoxCollider2D> aaBoxCollider = std::make_shared<AABoxCollider2D>(owner, optionalRigidbody, isTrigger, size);
	Physics2DManager::GetInstance()->AddAABoxCollider(aaBoxCollider);
	return aaBoxCollider;
}



GameObject* SceneCreateUtilities::CreateInvisibleWall(const Vector2<float>& position, const Vector2<float>& size)
{
	GameObject* wallGameObject = CreateGameObject(position, "Invisible Wall");
	std::shared_ptr<AABoxCollider2D> collider = CreateAABoxColliderComponent(wallGameObject, nullptr, false, size);

	std::shared_ptr<AABoxColliderDrawer> colliderDrawer = std::make_shared<AABoxColliderDrawer>(collider);
	wallGameObject->AttachBehaviour(colliderDrawer);

	return wallGameObject;
}



std::shared_ptr<UIButton> SceneCreateUtilities::CreateButton(const std::shared_ptr<Renderer>& renderer, const ColorBlock& colorBlock)
{
	std::shared_ptr<UIButton> button = std::make_shared<UIButton>(renderer, colorBlock);
	UICaster::GetInstance()->AddSelectable(button);
	return button;
}


