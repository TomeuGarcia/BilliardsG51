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

	std::shared_ptr<Image> image =
		CreateImageComponent(backgroundGameObject, GameAssetResources::GetInstance()->GetDebugImageData(), Vector2<int>(400, 400));

	std::shared_ptr<Text> text = CreateTextComponent(backgroundGameObject, GameAssetResources::GetInstance()->GetDebugTextFontData(),
													 "Nomadic Defender", 64);

	std::shared_ptr<TestBehaviour> test = std::make_shared<TestBehaviour>(image, text);
	backgroundGameObject->AttachBehaviour(test);



}

void EmptyScene::Start()
{
	GameRenderManager::GetInstance()->SetBackgroundColor(m_backgroundColor);
}
