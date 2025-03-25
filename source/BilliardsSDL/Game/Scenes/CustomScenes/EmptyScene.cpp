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
	GameObject* testGameObject = 
		CreateGameObject(Vector2<float>(0.0f, 2.0f));

	std::shared_ptr<Image> image =
		CreateImageComponent(testGameObject, GameAssetResources::GetInstance()->GetDebugTransparentImageData(), Vector2<float>(1.0f, 1.0f));

	std::shared_ptr<Text> text = 
		CreateTextComponent(testGameObject, GameAssetResources::GetInstance()->GetDebugTextFontData(), "Nomadic Defender", 64);

	std::shared_ptr<TestBehaviour> testBehaviour = std::make_shared<TestBehaviour>(image, text);
	testGameObject->AttachBehaviour(testBehaviour);
}

void EmptyScene::DoStart()
{
	GameRenderManager::GetInstance()->SetBackgroundColor(m_backgroundColor);
}
