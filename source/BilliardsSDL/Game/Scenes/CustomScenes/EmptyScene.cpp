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
	Vector2<float> position{ 0.0f, 2.0f };
	GameObject* backgroundGameObject = CreateGameObject(position);

	std::shared_ptr<Image> image =
		CreateImageComponent(backgroundGameObject, GameAssetResources::GetInstance()->GetDebugTransparentImageData(), Vector2<float>(1, 1));

	std::shared_ptr<Text> text = CreateTextComponent(backgroundGameObject, GameAssetResources::GetInstance()->GetDebugTextFontData(),
													 "Nomadic Defender", 64);

	std::shared_ptr<TestBehaviour> test = std::make_shared<TestBehaviour>(image, text);
	backgroundGameObject->AttachBehaviour(test);



}

void EmptyScene::Start()
{
	GameRenderManager::GetInstance()->SetBackgroundColor(m_backgroundColor);
}
