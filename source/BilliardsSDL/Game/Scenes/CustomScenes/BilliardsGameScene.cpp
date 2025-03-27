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
	CreateBoardHoles(boardPosition);

	

	BilliardStick* redStick = CreateBilliardStick(boardPosition + Vector2<float>(3, 3),
		GameAssetResources::GetInstance()->GetRedStickImageData(), "Red stick");
	BilliardStick* blueStick = CreateBilliardStick(boardPosition + Vector2<float>(-3, 3),
		GameAssetResources::GetInstance()->GetBlueStickImageData(), "Blue stick");
	
	manager->Init(redStick);


	const Vector2<float> randomBounds{ 2.0f, 1.0f };

	const Vector2<float> ballSize{ 0.25f, 0.25f };
	std::array<BilliardBall*, 16> balls{};


	BilliardBall* whiteBall = CreateBilliardBall(GameRandom::GetInstance()->GetRandomVectorBetweenSignedBounds(randomBounds), 
												 GameAssetResources::GetInstance()->GetWhiteBallImageData(), 0);
	balls[0] = whiteBall;


	BilliardBall* blackBall = CreateBilliardBall(GameRandom::GetInstance()->GetRandomVectorBetweenSignedBounds(randomBounds), 
												 GameAssetResources::GetInstance()->GetBlackBallImageData(), 8);
	balls[1] = blackBall;


	for (size_t i = 2; i < 2 + 7; ++i)
	{
		BilliardBall* ball = CreateBilliardBall(GameRandom::GetInstance()->GetRandomVectorBetweenSignedBounds(randomBounds), 
												GameAssetResources::GetInstance()->GetRedBallImageData(), i);
		balls[i] = ball;
	}
	
	for (size_t i = 2 + 7; i < balls.size(); ++i)
	{
		BilliardBall* ball = CreateBilliardBall(GameRandom::GetInstance()->GetRandomVectorBetweenSignedBounds(randomBounds), 
												GameAssetResources::GetInstance()->GetBlueBallImageData(), i);
		balls[i] = ball;
	}




	
	const std::array<Vector2<float>, 16> arrangedPositions = SortBallsAndComputeArrangePositions(balls, boardPosition, 0, 1);
	for (size_t i = 0; i < arrangedPositions.size(); ++i)
	{
		balls[i]->SetPosition(arrangedPositions[i]);
	}
	
}

void BilliardsGameScene::DoStart()
{
	GameRenderManager::GetInstance()->SetBackgroundColor(Colors::SoftBlue);
}

void BilliardsGameScene::DoUpdate()
{
	Vector2<int> mouseWindowPosition = GameInput::GetInstance()->GetMouseWindowPosition();
	Vector2<float> mouseWorldPosition = GameInput::GetInstance()->GetMouseWorldPosition();


	const float radius = 0.5f;
	if (GameInput::GetInstance()->GetKey(KeyCode::MouseRight))
	{
		GameRenderManager::GetInstance()->DrawDebugRect(Colors::White, 
			Rect<int>(mouseWindowPosition, GameSpacesComputer::GetInstance()->WorldToWindowVector({ radius*2, radius*2 })));
	}
	if (GameInput::GetInstance()->GetKeyUp(KeyCode::MouseRight))
	{
		std::list<Collider2D*> overlaps = Physics2DManager::GetInstance()->CircleOverlap(
			mouseWorldPosition, radius);

		printf("Overlaps: %i \n", overlaps.size());


		std::list<BilliardBall*> ballOverlaps{};
		for (auto it = overlaps.begin(); it != overlaps.end(); ++it)
		{
			const std::vector<std::shared_ptr<Behaviour>>& behaviours = (*it)->GetGameObject()->GetBehaviours();

			for (int i = 0; i < behaviours.size(); ++i)
			{
				BilliardBall* ball = dynamic_cast<BilliardBall*>(behaviours[i].get());
				if (ball != nullptr)
				{
					ballOverlaps.push_back(ball);
				}
			}
		}

		
		printf("Balls: %i \n", ballOverlaps.size());
	}


	if (GameInput::GetInstance()->GetKeyDown(KeyCode::R))
	{
		SceneManager::GetInstance()->LoadScene(SceneName::BilliardGame);
		system("cls");
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



BilliardBall* BilliardsGameScene::CreateBilliardBall(const Vector2<float>& position, const ImageResourceData& imageData, const int& number)
{
	const float ballDiameter{ 0.25f };
	const float ballRadius{ ballDiameter / 2.0f };
	const Vector2<float> ballSize{ ballDiameter, ballDiameter };

	GameObject* ballGameObject = CreateGameObject(position, "Ball_" + std::to_string(number));
	CreateImageComponent(ballGameObject, imageData, ballSize);

	std::shared_ptr<PhysicMaterial> physicMaterial = std::make_shared<PhysicMaterial>(0.5f, 2.25f);
	std::shared_ptr<Rigidbody2D> rigidbody = CreateRigidbodyComponent(ballGameObject, physicMaterial, 1.0f, 0.0f);
	std::shared_ptr<CircleCollider2D> collider = CreateCircleColliderComponent(ballGameObject, rigidbody.get(), false, ballRadius);

	std::shared_ptr<BilliardBall> billiardBall = std::make_shared<BilliardBall>(rigidbody);
	ballGameObject->AttachBehaviour(billiardBall);

	std::shared_ptr<CircleColliderDrawer> colliderDrawer = std::make_shared<CircleColliderDrawer>(collider);
	ballGameObject->AttachBehaviour(colliderDrawer);

	return billiardBall.get();
}

void BilliardsGameScene::CreateBoardWalls(const Vector2<float>& boardCenter)
{
	const Vector2<float> horizontalsSize{ 4.1f, 0.45f };

	const Vector2<float> topRightOffset{ 2.3f, 2.53f };
	const Vector2<float> topLeftOffset{ -2.25f, 2.53f };

	const Vector2<float> bottomRightOffset{ 2.3f , -2.6f };
	const Vector2<float> bottomLeftOffset{ -2.25f , -2.6f };
	CreateInvisibleWall(boardCenter + topRightOffset, horizontalsSize);
	CreateInvisibleWall(boardCenter + topLeftOffset, horizontalsSize);
	CreateInvisibleWall(boardCenter + bottomRightOffset, horizontalsSize);
	CreateInvisibleWall(boardCenter + bottomLeftOffset, horizontalsSize);


	const Vector2<float> verticalSize{ 0.45f, 4.25f };

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



void BilliardsGameScene::CreateBoardHoles(const Vector2<float>& boardCenter)
{
	const float holeRadius = 0.3f;

	const Vector2<float> topRightOffset{ 4.7f, 2.4f };
	CreateBoardHole(boardCenter + topRightOffset, holeRadius, "Hole_TopRight");

	const Vector2<float> topCenterOffset{ 0.0f, 2.53f };
	CreateBoardHole(boardCenter + topCenterOffset, holeRadius, "Hole_TopCenter");

	const Vector2<float> topLeftOffset{ -4.62f, 2.4f };
	CreateBoardHole(boardCenter + topLeftOffset, holeRadius, "Hole_TopLeft");


	const Vector2<float> bottomRightOffset{ 4.7f, -2.48f };
	CreateBoardHole(boardCenter + bottomRightOffset, holeRadius, "Hole_BottomRight");

	const Vector2<float> bottomCenterOffset{ 0.0f, -2.53f };
	CreateBoardHole(boardCenter + bottomCenterOffset, holeRadius, "Hole_BottomCenter");

	const Vector2<float> bottomLeftOffset{ -4.62f, -2.48f };
	CreateBoardHole(boardCenter + bottomLeftOffset, holeRadius, "Hole_BottomLeft");
}

GameObject* BilliardsGameScene::CreateBoardHole(const Vector2<float>& position, const float& radius, const std::string& holeName)
{
	GameObject* holeGameObject = CreateGameObject(position, holeName);
	std::shared_ptr<CircleCollider2D> collider = CreateCircleColliderComponent(holeGameObject, nullptr, true, radius);

	std::shared_ptr<CircleColliderDrawer> colliderDrawer = std::make_shared<CircleColliderDrawer>(collider);
	holeGameObject->AttachBehaviour(colliderDrawer);

	return holeGameObject;
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
