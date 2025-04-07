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
	for (int i = 0; i < 20; ++i) 
	{
		GameObject* testGameObject =
			GetCreateUtilities().CreateGameObject(Vector2<float>(i -5, i - 5), "Test_" + std::to_string(i));

		std::shared_ptr<Image> image =
			GetCreateUtilities().CreateImageComponent(testGameObject, GameAssetResources::GetInstance()->GetDebugTransparentImageData());

		std::shared_ptr<Text> text =
			GetCreateUtilities().CreateTextComponent(testGameObject, GameAssetResources::GetInstance()->GetDebugTextFontData(), "Nomadic Defender", 64);

		std::shared_ptr<TestBehaviour> testBehaviour = std::make_shared<TestBehaviour>(image, text);
		testGameObject->AttachBehaviour(testBehaviour);
	}
}

void EmptyScene::DoStart()
{
	GameRenderManager::GetInstance()->SetBackgroundColor(m_backgroundColor);
}

void EmptyScene::DoUpdate()
{
}
