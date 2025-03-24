#include "EmptyScene.h"

EmptyScene::EmptyScene(const Color& backgroundColor)
	: Scene(), m_backgroundColor(backgroundColor)
{

}

EmptyScene::~EmptyScene()
{
}


void EmptyScene::CreateGameObjects()
{		
	Vector2<int> position = GameRenderManager::GetInstance()->GetWindowSize() / 2;
	GameObject* backgroundGameObject = CreateGameObject(position);

	CreateImageComponent(backgroundGameObject, GameAssetResources::GetInstance()->GetDebugImageData(), Vector2<int>(400, 400));
}

void EmptyScene::Start()
{
	GameRenderManager::GetInstance()->SetBackgroundColor(m_backgroundColor);
}
