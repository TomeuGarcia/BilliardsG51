#include "BilliardsGameScene.h"

void BilliardsGameScene::CreateGameObjects()
{
	const Vector2<float> boardPosition = Vector2<float>::Zero();
	GameObject* board = CreateGameObject(boardPosition);
	CreateImageComponent(board, GameAssetResources::GetInstance()->GetBoardImageData(), Vector2<float>(10.0f, 5.6f));

	CreateBoardWalls(boardPosition);


	GameObject* redStick = CreateGameObject(boardPosition + Vector2<float>(3, 3));
	CreateImageComponent(redStick, GameAssetResources::GetInstance()->GetRedStickImageData(), Vector2<float>(3.0f, 0.1f));
	
	GameObject* blueStick = CreateGameObject(boardPosition + Vector2<float>(-3, 3));
	CreateImageComponent(blueStick, GameAssetResources::GetInstance()->GetBlueStickImageData(), Vector2<float>(3.0f, 0.1f));


	const Vector2<float> randomBounds{ 2.0f, 1.0f };

	const Vector2<float> ballSize{ 0.25f, 0.25f };
	std::array<BilliardBall*, 9> balls{}; // <---------- should be 16

	BilliardBall* whiteBall = CreateBilliardBall(GameRandom::GetInstance()->GetRandomVectorBetweenSignedBounds(randomBounds), 
												 GameAssetResources::GetInstance()->GetWhiteBallImageData());
	balls[0] = whiteBall;

	BilliardBall* blackBall = CreateBilliardBall(GameRandom::GetInstance()->GetRandomVectorBetweenSignedBounds(randomBounds), 
												 GameAssetResources::GetInstance()->GetBlackBallImageData());
	balls[1] = blackBall;


	for (size_t i = 2; i < 2 + 7; ++i)
	{
		BilliardBall* ball = CreateBilliardBall(GameRandom::GetInstance()->GetRandomVectorBetweenSignedBounds(randomBounds), 
												GameAssetResources::GetInstance()->GetRedBallImageData());
		balls[i] = ball;
	}
	
	for (size_t i = 2 + 7; i < balls.size(); ++i)
	{
		BilliardBall* ball = CreateBilliardBall(GameRandom::GetInstance()->GetRandomVectorBetweenSignedBounds(randomBounds), 
												GameAssetResources::GetInstance()->GetBlueBallImageData());
		balls[i] = ball;
	}




	/*
	const std::array<Vector2<float>, 16> arrangedPositions = SortBallsAndComputeArrangePositions(balls, boardPosition, 0, 1);
	for (size_t i = 0; i < arrangedPositions.size(); ++i)
	{
		balls[i]->GetTransform()->p_worldPosition = arrangedPositions[i];
	}
	*/
}

void BilliardsGameScene::DoStart()
{
	GameRenderManager::GetInstance()->SetBackgroundColor(Colors::SoftBlue);
}



BilliardBall* BilliardsGameScene::CreateBilliardBall(const Vector2<float>& position, const ImageResourceData& imageData)
{
	const float ballDiameter{ 0.25f };
	const float ballRadius{ ballDiameter / 2.0f };
	const Vector2<float> ballSize{ ballDiameter, ballDiameter };

	GameObject* ballGameObject = CreateGameObject(position);
	CreateImageComponent(ballGameObject, imageData, ballSize);

	std::shared_ptr<PhysicMaterial> physicMaterial = std::make_shared<PhysicMaterial>(1.0f, 4.0f);
	std::shared_ptr<Rigidbody2D> rigidbody = CreateRigidbodyComponent(ballGameObject, physicMaterial, 1.0f, 0.0f);
	std::shared_ptr<CircleCollider2D> collider = CreateCircleColliderComponent(ballGameObject, rigidbody.get(), ballRadius);

	std::shared_ptr<BilliardBall> billiardBall = std::make_shared<BilliardBall>(rigidbody);
	ballGameObject->AttachBehaviour(billiardBall);

	return billiardBall.get();
}

void BilliardsGameScene::CreateBoardWalls(const Vector2<float>& boardCenter)
{
	const Vector2<float> horizontalsSize{ 4.1f, 0.45f };

	const float hSidewaysOffset{ 2.3f };
	const float hVerticalOffset{ 2.5f };

	const Vector2<float> topRightOffset{ 2.3f, 2.53f };
	const Vector2<float> topLeftOffset{ -2.25f, 2.53f };

	const Vector2<float> bottomRightOffset{ 2.3f , -2.6f };
	const Vector2<float> bottomLeftOffset{ -2.25f , -2.6f };
	CreateInvisibleWall(boardCenter + topRightOffset, horizontalsSize);
	CreateInvisibleWall(boardCenter + topLeftOffset, horizontalsSize);
	CreateInvisibleWall(boardCenter + bottomRightOffset, horizontalsSize);
	CreateInvisibleWall(boardCenter + bottomLeftOffset, horizontalsSize);


	const Vector2<float> verticalSize{ 0.45f, 4.15f };

	const Vector2<float> rightOffset{ 4.8f, -0.05f };
	const Vector2<float> leftOffset{ -4.75f, -0.05f };
	CreateInvisibleWall(boardCenter + rightOffset, verticalSize);
	CreateInvisibleWall(boardCenter + leftOffset, verticalSize);
}


GameObject* BilliardsGameScene::CreateInvisibleWall(const Vector2<float>& position, const Vector2<float>& size)
{
	GameObject* wallGameObject = CreateGameObject(position);
	std::shared_ptr<AABoxCollider2D> collider = CreateAABoxColliderComponent(wallGameObject, nullptr, size);

	std::shared_ptr<AABoxColliderDrawer> colliderDrawer = std::make_shared<AABoxColliderDrawer>(collider);
	wallGameObject->AttachBehaviour(colliderDrawer);

	return wallGameObject;
}



const std::array<Vector2<float>, 16> BilliardsGameScene::SortBallsAndComputeArrangePositions(std::array<BilliardBall*, 16>& balls,
				const Vector2<float> boardCenterPosition, const int& whiteBallIndex, const int& blackBallIndex)
{
	BilliardBall* originalLast = balls[balls.size() - 1];
	balls[balls.size() - 1] = balls[whiteBallIndex];
	balls[whiteBallIndex] = originalLast;

	BilliardBall* originalFifth = balls[4];
	balls[4] = balls[blackBallIndex];
	balls[blackBallIndex] = originalFifth;



	const float ballDiameter{ 0.25f };
	const float ballSideDisplacement{ ballDiameter * 0.85f };
	const float ballUpDisplacement{ 0.25f };
	const float startingDisplacement = 2.25f;


	std::array<Vector2<float>, 16> arrangedPositions{};
	arrangedPositions[arrangedPositions.size() - 1] = boardCenterPosition + (Vector2<float>::Right() * startingDisplacement);


	Vector2<float> ballStartPosition = boardCenterPosition;
	ballStartPosition += Vector2<float>::Left() * startingDisplacement;
	
	int column{ 0 };
	int ballsPerColumn{ 1 };
	int ballInColumn{ 0 };
	for (size_t i = 0; i < balls.size() - 1; ++i)
	{
		Vector2<float> ballPosition = ballStartPosition;
		ballPosition += Vector2<float>::Left() * ((ballSideDisplacement) * column);
		ballPosition += Vector2<float>::Up() * (ballUpDisplacement * (ballInColumn - (ballsPerColumn / 2.0f)));

		arrangedPositions[i] = ballPosition;

		++ballInColumn;
		if (ballInColumn >= ballsPerColumn)
		{
			ballInColumn = 0;
			++ballsPerColumn;
			++column;
		}
	}

	return arrangedPositions;
}
