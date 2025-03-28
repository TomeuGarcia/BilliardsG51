#include "BilliardsGameScene.h"

void BilliardsGameScene::CreateGameObjects()
{
	GameObject* managerGameObject = CreateGameObject(Vector2<float>::Zero(), "Manager");
	std::shared_ptr<BilliardsGameplayManager> manager = std::make_shared<BilliardsGameplayManager>();
	managerGameObject->AttachBehaviour(manager);


	const Vector2<float> boardPosition = Vector2<float>::Zero();
	GameObject* board = CreateGameObject(boardPosition, "Board");
	CreateImageComponent(board, GameAssetResources::GetInstance()->GetBoardImageData(), Vector2<float>(10.0f, 5.6f));

	CreateBoardWalls(boardPosition);
	CreateBoardHoles(boardPosition, manager.get());	

	std::vector<BilliardBall*> balls = CreateBilliardBalls();

	BilliardStick* redStick = CreateBilliardStick(boardPosition + Vector2<float>(3, 3),
		GameAssetResources::GetInstance()->GetRedStickImageData(), "Red stick");
	BilliardStick* blueStick = CreateBilliardStick(boardPosition + Vector2<float>(-3, 3),
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




BilliardStick* BilliardsGameScene::CreateBilliardStick(const Vector2<float>& position, const ImageResourceData& imageData, const std::string& name)
{
	GameObject* stickGameObject = CreateGameObject(position, name);
	std::shared_ptr<Image> image = CreateImageComponent(stickGameObject, imageData, Vector2<float>(3.0f, 0.1f));

	std::shared_ptr<BilliardStick> billiardStick = std::make_shared<BilliardStick>(
		stickGameObject->GetTransform(), image.get(), Vector2<float>::Left(), 2.5f, 1.5f);
	stickGameObject->AttachBehaviour(billiardStick);

	return billiardStick.get();
}



std::vector<BilliardBall*> BilliardsGameScene::CreateBilliardBalls()
{
	std::vector<BilliardBall*> balls(16);

	const Vector2<float> randomBounds{ 2.0f, 1.0f };
	const Vector2<float> ballSize{ 0.25f, 0.25f };


	BilliardBall* whiteBall = CreateBilliardBall(GameRandom::GetInstance()->GetRandomVectorBetweenSignedBounds(randomBounds),
		GameAssetResources::GetInstance()->GetWhiteBallImageData(), BilliardBall::ColorType::White, 0);
	balls[0] = whiteBall;

	for (size_t i = 1; i < 1 + 7; ++i)
	{
		BilliardBall* ball = CreateBilliardBall(GameRandom::GetInstance()->GetRandomVectorBetweenSignedBounds(randomBounds),
			GameAssetResources::GetInstance()->GetRedBallImageData(), BilliardBall::ColorType::Red, i);
		balls[i] = ball;
	}

	BilliardBall* blackBall = CreateBilliardBall(GameRandom::GetInstance()->GetRandomVectorBetweenSignedBounds(randomBounds),
		GameAssetResources::GetInstance()->GetBlackBallImageData(), BilliardBall::ColorType::Black, 8);
	balls[8] = blackBall;

	for (size_t i = 2 + 7; i < balls.size(); ++i)
	{
		BilliardBall* ball = CreateBilliardBall(GameRandom::GetInstance()->GetRandomVectorBetweenSignedBounds(randomBounds),
			GameAssetResources::GetInstance()->GetBlueBallImageData(), BilliardBall::ColorType::Blue, i);
		balls[i] = ball;
	}

	return balls;
}

BilliardBall* BilliardsGameScene::CreateBilliardBall(const Vector2<float>& position, const ImageResourceData& imageData, 
	const BilliardBall::ColorType& colorType, const int& number)
{
	const float ballDiameter{ 0.25f };
	const float ballRadius{ ballDiameter / 2.0f };
	const Vector2<float> ballSize{ ballDiameter, ballDiameter };

	GameObject* ballGameObject = CreateGameObject(position, "Ball_" + std::to_string(number));
	std::shared_ptr<Image> image = CreateImageComponent(ballGameObject, imageData, ballSize);

	std::shared_ptr<PhysicMaterial> physicMaterial = std::make_shared<PhysicMaterial>(0.5f, 2.25f);
	std::shared_ptr<Rigidbody2D> rigidbody = CreateRigidbodyComponent(ballGameObject, physicMaterial, 1.0f, 0.0f);
	std::shared_ptr<CircleCollider2D> collider = CreateCircleColliderComponent(ballGameObject, rigidbody.get(), false, ballRadius);

	std::shared_ptr<BilliardBall> billiardBall = std::make_shared<BilliardBall>(collider, rigidbody, image, colorType);
	ballGameObject->AttachBehaviour(billiardBall);

	std::shared_ptr<CircleColliderDrawer> colliderDrawer = std::make_shared<CircleColliderDrawer>(collider);
	ballGameObject->AttachBehaviour(colliderDrawer);

	return billiardBall.get();
}



void BilliardsGameScene::CreateBoardWalls(const Vector2<float>& boardCenter)
{
	const Vector2<float> horizontalsSize{ 4.0f, 0.45f };

	const Vector2<float> topRightOffset{ 2.3f, 2.53f };
	const Vector2<float> topLeftOffset{ -2.25f, 2.53f };

	const Vector2<float> bottomRightOffset{ 2.3f , -2.6f };
	const Vector2<float> bottomLeftOffset{ -2.25f , -2.6f };
	CreateInvisibleWall(boardCenter + topRightOffset, horizontalsSize);
	CreateInvisibleWall(boardCenter + topLeftOffset, horizontalsSize);
	CreateInvisibleWall(boardCenter + bottomRightOffset, horizontalsSize);
	CreateInvisibleWall(boardCenter + bottomLeftOffset, horizontalsSize);


	const Vector2<float> verticalSize{ 0.45f, 4.15f };

	const Vector2<float> rightOffset{ 4.8f, -0.04f };
	const Vector2<float> leftOffset{ -4.75f, -0.04f };
	CreateInvisibleWall(boardCenter + rightOffset, verticalSize);
	CreateInvisibleWall(boardCenter + leftOffset, verticalSize);
}



GameObject* BilliardsGameScene::CreateInvisibleWall(const Vector2<float>& position, const Vector2<float>& size)
{
	GameObject* wallGameObject = CreateGameObject(position, "Invisible Wall");
	std::shared_ptr<AABoxCollider2D> collider = CreateAABoxColliderComponent(wallGameObject, nullptr, false, size);

	std::shared_ptr<AABoxColliderDrawer> colliderDrawer = std::make_shared<AABoxColliderDrawer>(collider);
	wallGameObject->AttachBehaviour(colliderDrawer);

	return wallGameObject;
}



void BilliardsGameScene::CreateBoardHoles(const Vector2<float>& boardCenter,
	IBilliardBoardHoleInteractionsManager* holeInteractionManager)
{
	const float holeRadius = 0.35f;

	const Vector2<float> topRightOffset{ 4.7f, 2.4f };
	CreateBoardHole(boardCenter + topRightOffset, holeRadius, "Hole_TopRight", holeInteractionManager);

	const Vector2<float> topCenterOffset{ 0.0f, 2.53f };
	CreateBoardHole(boardCenter + topCenterOffset, holeRadius, "Hole_TopCenter", holeInteractionManager);

	const Vector2<float> topLeftOffset{ -4.62f, 2.4f };
	CreateBoardHole(boardCenter + topLeftOffset, holeRadius, "Hole_TopLeft", holeInteractionManager);


	const Vector2<float> bottomRightOffset{ 4.7f, -2.48f };
	CreateBoardHole(boardCenter + bottomRightOffset, holeRadius, "Hole_BottomRight", holeInteractionManager);

	const Vector2<float> bottomCenterOffset{ 0.0f, -2.53f };
	CreateBoardHole(boardCenter + bottomCenterOffset, holeRadius, "Hole_BottomCenter", holeInteractionManager);

	const Vector2<float> bottomLeftOffset{ -4.62f, -2.48f };
	CreateBoardHole(boardCenter + bottomLeftOffset, holeRadius, "Hole_BottomLeft", holeInteractionManager);
}

GameObject* BilliardsGameScene::CreateBoardHole(const Vector2<float>& position, const float& radius, const std::string& holeName,
	IBilliardBoardHoleInteractionsManager* holeInteractionManager)
{
	GameObject* holeGameObject = CreateGameObject(position, holeName);
	std::shared_ptr<CircleCollider2D> collider = CreateCircleColliderComponent(holeGameObject, nullptr, true, radius);

	std::shared_ptr<CircleColliderDrawer> colliderDrawer = std::make_shared<CircleColliderDrawer>(collider);
	holeGameObject->AttachBehaviour(colliderDrawer);

	std::shared_ptr<BilliardsBoardHole> hole = std::make_shared<BilliardsBoardHole>(holeGameObject->GetTransform(), holeInteractionManager);
	holeGameObject->AttachBehaviour(hole);

	return holeGameObject;
}







