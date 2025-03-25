#include "BilliardsGameScene.h"

void BilliardsGameScene::CreateGameObjects()
{

	const Vector2<float> boardPosition = Vector2<float>::Zero();
	GameObject* board = CreateGameObject(boardPosition);
	CreateImageComponent(board, GameAssetResources::GetInstance()->GetBoardImageData(), Vector2<float>(10.0f, 5.6f));


	GameObject* redStick = CreateGameObject(boardPosition + Vector2<float>(3, 3));
	CreateImageComponent(redStick, GameAssetResources::GetInstance()->GetRedStickImageData(), Vector2<float>(3.0f, 0.1f));
	
	GameObject* blueStick = CreateGameObject(boardPosition + Vector2<float>(-3, 3));
	CreateImageComponent(blueStick, GameAssetResources::GetInstance()->GetBlueStickImageData(), Vector2<float>(3.0f, 0.1f));


	const Vector2<float> randomBounds{ 4.0f, 2.0f };

	const Vector2<float> ballSize{ 0.25f, 0.25f };
	std::array<BilliardBall*, 16> balls{};

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
	std::shared_ptr<CircleCollider2D> collider = CreateCircleColliderComponent(ballGameObject, ballRadius);
	std::shared_ptr<Rigidbody2D> rigidbody = CreateRigidbodyComponent(collider, physicMaterial, 1.0f, 0.0f);

	std::shared_ptr<BilliardBall> billiardBall = std::make_shared<BilliardBall>(rigidbody);
	ballGameObject->AttachBehaviour(billiardBall);

	return billiardBall.get();
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
