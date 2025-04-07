#include "BilliardsGameScene.h"

void BilliardsGameScene::CreateGameObjects()
{
	GameObject* managerGameObject = GetCreateUtilities().CreateGameObject(Vector2<float>::Zero(), "Manager");
	std::shared_ptr<BilliardsGameplayManager> manager = std::make_shared<BilliardsGameplayManager>();
	managerGameObject->AttachBehaviour(manager);


	const Vector2<float> boardPosition = Vector2<float>::Zero();
	GetPrefabUtilities().CreateBilliardsBoard(boardPosition, manager.get());


	std::vector<BilliardBall*> balls = GetPrefabUtilities().CreateBilliardsGameBalls();

	BilliardStick* redStick = GetPrefabUtilities().CreateBilliardsStick(boardPosition + Vector2<float>(3, 3),
		GameAssetResources::GetInstance()->GetRedStickImageData(), "Red stick");
	BilliardStick* blueStick = GetPrefabUtilities().CreateBilliardsStick(boardPosition + Vector2<float>(-3, 3),
		GameAssetResources::GetInstance()->GetBlueStickImageData(), "Blue stick");


	manager->Init(balls, boardPosition, redStick, blueStick);	
}



void BilliardsGameScene::DoStart()
{
	AABoxColliderDrawer::s_enabled = false;
	CircleColliderDrawer::s_enabled = false;
}

void BilliardsGameScene::DoUpdate()
{
	if (GameInput::GetInstance()->GetKeyDown(KeyCode::C))
	{
		AABoxColliderDrawer::s_enabled = !AABoxColliderDrawer::s_enabled;
		CircleColliderDrawer::s_enabled = !CircleColliderDrawer::s_enabled;
	}
}

