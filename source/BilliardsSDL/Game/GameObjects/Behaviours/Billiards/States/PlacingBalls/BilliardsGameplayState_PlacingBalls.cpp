#include "BilliardsGameplayState_PlacingBalls.h"

BilliardsGameplayState_PlacingBalls::BilliardsGameplayState_PlacingBalls(BilliardsGameplayStateBlackboard* blackboard)
    : BilliardsGameplayState(blackboard), m_placingTimer(0.0f)
{
}

BilliardsGameplayState_PlacingBalls::~BilliardsGameplayState_PlacingBalls()
{
}



void BilliardsGameplayState_PlacingBalls::DoEnter()
{
	SetBallsIgnoringPhysics();
	StartPlacingBalls();
}

bool BilliardsGameplayState_PlacingBalls::Update()
{
	m_placingTimer.Update(GameTime::GetInstance()->GetDeltaTime());

	if (m_placingTimer.HasFinished())
	{
		GetBlackboard()->GetSpecialEventsManager()->OnPlayerStartsPlaying();
		SetNextState(Type::Thinking_Red);
		return true;
	}

    return false;
}

void BilliardsGameplayState_PlacingBalls::Exit()
{
	SetBallsCheckingPhysics();
}





void BilliardsGameplayState_PlacingBalls::SetBallsIgnoringPhysics()
{
	const std::vector<BilliardBall*>& balls = GetBlackboard()->GetBalls();
	for (auto it = balls.begin(); it != balls.end(); ++it)
	{
		(*it)->SetIgnoringPhysics();
	}
}

void BilliardsGameplayState_PlacingBalls::SetBallsCheckingPhysics()
{
	const std::vector<BilliardBall*>& balls = GetBlackboard()->GetBalls();
	for (auto it = balls.begin(); it != balls.end(); ++it)
	{
		(*it)->SetUsingPhysics();
	}
}




void BilliardsGameplayState_PlacingBalls::StartPlacingBalls()
{
	const std::vector<BilliardBall*>& balls = GetBlackboard()->GetBalls();

	std::vector<Vector2<float>> placingPositions = ComputeArrangedSortedPositions(
		GetBlackboard()->GetBoardCenter(), balls, 0, 8);

	ShuffleBallPositions(placingPositions, { 1, 7 }, {9, 14});

	MoveBalls(balls, placingPositions);
}

std::vector<Vector2<float>> BilliardsGameplayState_PlacingBalls::ComputeArrangedSortedPositions(
	const Vector2<float>& boardCenter, const std::vector<BilliardBall*>& balls, 
	const int& whiteBallIndex, const int& blackBallIndex)
{
	const float ballDiameter{ 0.3f };
	const float ballSideDisplacement{ ballDiameter * 0.85f };
	const float ballUpDisplacement{ 0.3f };
	const float startingDisplacement = 2.25f;


	std::vector<Vector2<float>> arrangedPositions{ balls.size() };

	Vector2<float> ballStartPosition = boardCenter;
	ballStartPosition += Vector2<float>(-startingDisplacement, 0.15f);

	int column{ 0 };
	int ballsPerColumn{ 1 };
	int ballInColumn{ 0 };
	for (size_t i = 0; i < balls.size() - 1; ++i)
	{
		Vector2<float> ballPosition = ballStartPosition;
		ballPosition += Vector2<float>::Left() * ((ballSideDisplacement)*column);
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



	arrangedPositions[arrangedPositions.size() - 1] = boardCenter + (Vector2<float>::Right() * startingDisplacement);

	const Vector2<float> originalLast = arrangedPositions[arrangedPositions.size() - 1];
	arrangedPositions[arrangedPositions.size() - 1] = arrangedPositions[whiteBallIndex];
	arrangedPositions[whiteBallIndex] = originalLast;

	const Vector2<float> originalFifth = arrangedPositions[4];
	arrangedPositions[4] = arrangedPositions[blackBallIndex];
	arrangedPositions[blackBallIndex] = originalFifth;


	return arrangedPositions;
}


void BilliardsGameplayState_PlacingBalls::ShuffleBallPositions(std::vector<Vector2<float>>& ballPositions,
	const Vector2<int>& boundsA, const Vector2<int>& boundsB)
{
	const int tries = 5;
	for (int i = 0; i < tries; ++i)
	{
		int indexA = GameRandom::GetInstance()->GetRandomInt(boundsA.x, boundsA.y);
		int indexB = GameRandom::GetInstance()->GetRandomInt(boundsB.x, boundsB.y);

		const Vector2<float> tempA = ballPositions[indexA];
		ballPositions[indexA] = ballPositions[indexB];
		ballPositions[indexB] = tempA;
	}

}

void BilliardsGameplayState_PlacingBalls::MoveBalls(const std::vector<BilliardBall*>& balls, 
	const std::vector<Vector2<float>>& ballPositions)
{
	float moveSpeed = 5.0f;
	float moveDelay = 0.0f;

	float totalDuration = 0.0f;

	for (size_t i = 1; i < balls.size(); ++i)
	{
		Transform* ballTransform = balls[i]->GetTransform();
		const Vector2<float> goalPosition = ballPositions[i];

		const float distance = Vector2<float>::Distance(goalPosition, ballTransform->p_worldPosition);

		float duration = distance / moveSpeed;

		GameTweener::GetInstance()->TweenPosition(ballTransform, goalPosition, duration, moveDelay);

		totalDuration += duration;

		moveSpeed *= 1.1f;
		moveDelay += 0.1f;
	}

	GameTweener::GetInstance()->TweenPosition(balls[0]->GetTransform(), ballPositions[0], 0.5f, 1.5f);

	m_placingTimer.SetDuration(2.25f);
}
