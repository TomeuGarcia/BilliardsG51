#include "CustomPrefabUtilities.h"



CustomPrefabUtilities::CustomPrefabUtilities(SceneCreateUtilities* sceneCreateUtilities)
	: m_sceneCreateUtilities(sceneCreateUtilities)
{
}

BilliardBall* CustomPrefabUtilities::CreateBilliardsBall(const Vector2<float>& position, const ImageResourceData& imageData, 
	const BilliardBall::ColorType& colorType, const int& number)
{
	GameObject* ballGameObject = m_sceneCreateUtilities->CreateGameObject(position, "Ball_" + std::to_string(number));
	std::shared_ptr<Image> image = m_sceneCreateUtilities->CreateImageComponent(ballGameObject, imageData);
	image->p_scale = Vector2<float>::One() * 0.55f;

	const float ballRadius{ image->p_scale.x / 4.0f };

	std::shared_ptr<PhysicMaterial> physicMaterial = std::make_shared<PhysicMaterial>(0.5f, 2.25f);
	std::shared_ptr<Rigidbody2D> rigidbody = m_sceneCreateUtilities->CreateRigidbodyComponent(ballGameObject, physicMaterial, 1.0f, 0.0f);
	std::shared_ptr<CircleCollider2D> collider = m_sceneCreateUtilities->CreateCircleColliderComponent(ballGameObject, rigidbody.get(), false, ballRadius);

	std::shared_ptr<BilliardBall> billiardBall = std::make_shared<BilliardBall>(collider, rigidbody, image, colorType);
	ballGameObject->AttachBehaviour(billiardBall);

	std::shared_ptr<CircleColliderDrawer> colliderDrawer = std::make_shared<CircleColliderDrawer>(collider);
	ballGameObject->AttachBehaviour(colliderDrawer);

	return billiardBall.get();
}

std::vector<BilliardBall*> CustomPrefabUtilities::CreateBilliardsGameBalls()
{
	std::vector<BilliardBall*> balls(16);

	const Vector2<float> randomBounds{ 2.0f, 1.0f };
	const Vector2<float> ballSize{ 0.25f, 0.25f };


	BilliardBall* whiteBall = CreateBilliardsBall(GameRandom::GetInstance()->GetRandomVectorBetweenSignedBounds(randomBounds),
		GameAssetResources::GetInstance()->GetWhiteBallImageData(), BilliardBall::ColorType::White, 0);
	balls[0] = whiteBall;

	for (size_t i = 1; i < 1 + 7; ++i)
	{
		BilliardBall* ball = CreateBilliardsBall(GameRandom::GetInstance()->GetRandomVectorBetweenSignedBounds(randomBounds),
			GameAssetResources::GetInstance()->GetRedBallImageData(), BilliardBall::ColorType::Red, i);
		balls[i] = ball;
	}

	BilliardBall* blackBall = CreateBilliardsBall(GameRandom::GetInstance()->GetRandomVectorBetweenSignedBounds(randomBounds),
		GameAssetResources::GetInstance()->GetBlackBallImageData(), BilliardBall::ColorType::Black, 8);
	balls[8] = blackBall;

	for (size_t i = 2 + 7; i < balls.size(); ++i)
	{
		BilliardBall* ball = CreateBilliardsBall(GameRandom::GetInstance()->GetRandomVectorBetweenSignedBounds(randomBounds),
			GameAssetResources::GetInstance()->GetBlueBallImageData(), BilliardBall::ColorType::Blue, i);
		balls[i] = ball;
	}

	return balls;
}



BilliardStick* CustomPrefabUtilities::CreateBilliardsStick(const Vector2<float>& position, const ImageResourceData& imageData, const std::string& name)
{
	GameObject* stickGameObject = m_sceneCreateUtilities->CreateGameObject(position, name);
	std::shared_ptr<Image> image = m_sceneCreateUtilities->CreateImageComponent(stickGameObject, imageData);
	image->p_scale = Vector2<float>::One() * 0.58f;

	std::shared_ptr<BilliardStick> billiardStick = std::make_shared<BilliardStick>(
		stickGameObject->GetTransform(), image.get(), Vector2<float>::Left(), 2.5f, 1.5f);
	stickGameObject->AttachBehaviour(billiardStick);

	return billiardStick.get();
}



GameObject* CustomPrefabUtilities::CreateBilliardsBoard(const Vector2<float>& position, IBilliardBoardHoleInteractionsManager* holeInteractionManager)
{
	GameObject* board = m_sceneCreateUtilities->CreateGameObject(position, "Board");
	std::shared_ptr<Image> boardImage = m_sceneCreateUtilities->CreateImageComponent(board, GameAssetResources::GetInstance()->GetBoardImageData());
	boardImage->p_scale = Vector2<float>::One() * 0.55f;

	CreateBoardWalls(position);
	CreateBoardHoles(position, holeInteractionManager);

	return board;
}

void CustomPrefabUtilities::CreateBoardWalls(const Vector2<float>& boardCenter)
{
	const Vector2<float> horizontalsSize{ 4.0f, 0.45f };

	const Vector2<float> topRightOffset{ 2.38f, 2.6f };
	const Vector2<float> topLeftOffset{ -2.3f, 2.6f };

	const Vector2<float> bottomRightOffset{ 2.38f , -2.65f };
	const Vector2<float> bottomLeftOffset{ -2.3f , -2.65f };
	m_sceneCreateUtilities->CreateInvisibleWall(boardCenter + topRightOffset, horizontalsSize);
	m_sceneCreateUtilities->CreateInvisibleWall(boardCenter + topLeftOffset, horizontalsSize);
	m_sceneCreateUtilities->CreateInvisibleWall(boardCenter + bottomRightOffset, horizontalsSize);
	m_sceneCreateUtilities->CreateInvisibleWall(boardCenter + bottomLeftOffset, horizontalsSize);


	const Vector2<float> verticalSize{ 0.45f, 4.25f };

	const Vector2<float> rightOffset{ 4.95f, -0.03f };
	const Vector2<float> leftOffset{ -4.87f, -0.03f };
	m_sceneCreateUtilities->CreateInvisibleWall(boardCenter + rightOffset, verticalSize);
	m_sceneCreateUtilities->CreateInvisibleWall(boardCenter + leftOffset, verticalSize);
}


void CustomPrefabUtilities::CreateBoardHoles(const Vector2<float>& boardCenter, IBilliardBoardHoleInteractionsManager* holeInteractionManager)
{
	const float holeRadius = 0.23f;

	const Vector2<float> topRightOffset{ 4.75f, 2.45f };
	CreateBoardHole(boardCenter + topRightOffset, holeRadius, "Hole_TopRight", holeInteractionManager);

	const Vector2<float> topCenterOffset{ 0.02f, 2.52f };
	CreateBoardHole(boardCenter + topCenterOffset, holeRadius, "Hole_TopCenter", holeInteractionManager);

	const Vector2<float> topLeftOffset{ -4.7f, 2.45f };
	CreateBoardHole(boardCenter + topLeftOffset, holeRadius, "Hole_TopLeft", holeInteractionManager);


	const Vector2<float> bottomRightOffset{ 4.75f, -2.48f };
	CreateBoardHole(boardCenter + bottomRightOffset, holeRadius, "Hole_BottomRight", holeInteractionManager);

	const Vector2<float> bottomCenterOffset{ 0.02f, -2.55f };
	CreateBoardHole(boardCenter + bottomCenterOffset, holeRadius, "Hole_BottomCenter", holeInteractionManager);

	const Vector2<float> bottomLeftOffset{ -4.7f, -2.48f };
	CreateBoardHole(boardCenter + bottomLeftOffset, holeRadius, "Hole_BottomLeft", holeInteractionManager);
}


GameObject* CustomPrefabUtilities::CreateBoardHole(const Vector2<float>& position, const float& radius, const std::string& holeName, 
	IBilliardBoardHoleInteractionsManager* holeInteractionManager)
{
	GameObject* holeGameObject = m_sceneCreateUtilities->CreateGameObject(position, holeName);
	std::shared_ptr<CircleCollider2D> collider = m_sceneCreateUtilities->CreateCircleColliderComponent(holeGameObject, nullptr, true, radius);

	std::shared_ptr<CircleColliderDrawer> colliderDrawer = std::make_shared<CircleColliderDrawer>(collider);
	holeGameObject->AttachBehaviour(colliderDrawer);

	std::shared_ptr<BilliardsBoardHole> hole = std::make_shared<BilliardsBoardHole>(holeGameObject->GetTransform(), holeInteractionManager);
	holeGameObject->AttachBehaviour(hole);

	return holeGameObject;
}
