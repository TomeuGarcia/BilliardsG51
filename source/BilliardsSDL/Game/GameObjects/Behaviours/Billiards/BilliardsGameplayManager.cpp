#include "BilliardsGameplayManager.h"

BilliardsGameplayManager::BilliardsGameplayManager()
	: m_gameplayStatesMap(),
	m_currentState(nullptr),
	m_gameplayStatesBlackboard(),
	m_playerRed(),
	m_playerBlue(),
	m_wellplacedBallsThisTurn(),
	m_missplacedBallsThisTurn(),
	m_blackBallWellPlaced(false)
{
	m_wellplacedBallsThisTurn.reserve(5);
	m_missplacedBallsThisTurn.reserve(2);
}

BilliardsGameplayManager::~BilliardsGameplayManager()
{
}


void BilliardsGameplayManager::Init(const std::vector<BilliardBall*>& balls, const Vector2<float>& boardCenter, 
	BilliardStick* redStick, BilliardStick* blueStick)
{
	m_whiteBall = balls[0];
	m_blackBall = balls[8];


	std::set<BilliardBall*> remainingRedBalls{};
	std::set<BilliardBall*> remainingBlueBalls{};
	for (size_t i = 1; i < 1 + 7; ++i)
	{
		remainingRedBalls.emplace(balls[i]);
	}
	for (size_t i = 9; i < balls.size(); ++i)
	{
		remainingBlueBalls.emplace(balls[i]);
	}

	m_playerRed.Init(redStick, Colors::SoftRed, remainingRedBalls);
	m_playerBlue.Init(blueStick, Colors::SoftBlue, remainingBlueBalls);
	m_gameplayStatesBlackboard.Init(balls, boardCenter, &m_playerRed, &m_playerBlue, this);


	m_gameplayStatesMap[BilliardsGameplayState::Type::Init] = 
			  std::make_shared<BilliardsGameplayState_Init>(&m_gameplayStatesBlackboard);

	m_gameplayStatesMap[BilliardsGameplayState::Type::PlacingBalls] = 
			  std::make_shared<BilliardsGameplayState_PlacingBalls>(&m_gameplayStatesBlackboard);

	m_gameplayStatesMap[BilliardsGameplayState::Type::Thinking_Red] = 
			  std::make_shared<BilliardsGameplayState_PlayerThinking>(&m_gameplayStatesBlackboard, &m_playerRed);

	m_gameplayStatesMap[BilliardsGameplayState::Type::Thinking_Blue] = 
			  std::make_shared<BilliardsGameplayState_PlayerThinking>(&m_gameplayStatesBlackboard, &m_playerBlue);
	
	m_gameplayStatesMap[BilliardsGameplayState::Type::ResolvingBoard] = 
			  std::make_shared<BilliardsGameplayState_ResolvingBoard>(&m_gameplayStatesBlackboard);

	m_gameplayStatesMap[BilliardsGameplayState::Type::GameFinish] = 
			  std::make_shared<BilliardsGameplayState_GameFinish>(&m_gameplayStatesBlackboard);



	m_currentState = (m_gameplayStatesMap[BilliardsGameplayState::Type::Init]).get();
	m_currentState->Enter();
}



void BilliardsGameplayManager::Update()
{
	if (m_currentState->Update())
	{
		m_currentState->Exit();
		m_currentState = (m_gameplayStatesMap[m_currentState->GetNextState()]).get();
		m_currentState->Enter();
	}

	if (GameInput::GetInstance()->GetKeyDown(KeyCode::R))
	{
		SceneManager::GetInstance()->LoadScene(SceneName::BilliardGame);
	}
}

void BilliardsGameplayManager::OnDestroy()
{
	m_currentState->Exit();
}




bool BilliardsGameplayManager::TryHitWhiteBall(const Vector2<float>& position, const Vector2<float>& direction,
	const float& forceMagnitude)
{
	const Circle probingCircle{ position, 0.2f };

	bool intersecting = Math::AreCirclesIntersecting(probingCircle, m_whiteBall->GetCollisionCircle());
	if (!intersecting)
	{
		return false;
	}


	const Vector2<float> force = direction * forceMagnitude;
	m_whiteBall->ApplyForce(force);
	return true;


	/*
	std::list<Collider2D*> colliders = Physics2DManager::GetInstance()->CircleOverlap(position, 0.2f);

	std::vector<BilliardBall*> balls;
	balls.reserve(8);

	for (auto colliderIt = colliders.begin(); colliderIt != colliders.end(); ++colliderIt)
	{
		const std::vector<std::shared_ptr<Behaviour>>& behaviours = (*colliderIt)->GetGameObject()->GetBehaviours();

		for (auto behaviourIt = behaviours.begin(); behaviourIt != behaviours.end(); ++behaviourIt)
		{
			BilliardBall* ball = dynamic_cast<BilliardBall*>(behaviourIt->get());
			if (ball != nullptr)
			{
				balls.emplace_back(ball);

				ball->ApplyForce(force);
			}
		}
	}		

	return balls.size() > 0;
	*/
}



bool BilliardsGameplayManager::AllBallsStoppedMoving() const
{
	const std::vector<BilliardBall*>& balls = m_gameplayStatesBlackboard.GetBalls();

	for (auto it = balls.begin(); it != balls.end(); ++it)
	{
		if ((*it)->IsMoving())
		{
			return false;
		}
	}

	return true;
}



void BilliardsGameplayManager::OnBallEnteredHole(BilliardBall* ball, const Vector2<float> holeCenter)
{
	OnAnyBallEnteredHole(ball, holeCenter);

	switch (ball->GetColorType())
	{
	case BilliardBall::ColorType::White:
		OnWhiteBallEnteredHole();
		break;
	case BilliardBall::ColorType::Black:
		OnBlackBallEnteredHole();
		break;
	case BilliardBall::ColorType::Red:
		OnRedBallEnteredHole(ball);
		break;
	case BilliardBall::ColorType::Blue:
		OnBlueBallEnteredHole(ball);
		break;
	default:
		break;
	}
}



void BilliardsGameplayManager::OnAnyBallEnteredHole(BilliardBall* ball, const Vector2<float>& holeCenter)
{
	float ballSpeed = ball->GetCurrentSpeed();
	ball->SetIgnoringPhysics();	

	const float moveToHoleDuration = Vector2<float>::Distance(holeCenter, ball->GetTransform()->p_worldPosition) / ballSpeed;

	GameTweener::GetInstance()->TweenPosition(ball->GetTransform(), holeCenter, moveToHoleDuration, 0.0f);
}


void BilliardsGameplayManager::OnWhiteBallEnteredHole()
{
	m_missplacedBallsThisTurn.emplace_back(m_whiteBall);
}

void BilliardsGameplayManager::OnBlackBallEnteredHole()
{
	if (m_gameplayStatesBlackboard.GetCurrentPlayer()->StillHasRemainingColoredBalls())
	{
		m_missplacedBallsThisTurn.emplace_back(m_blackBall);
	}
	else
	{
		m_gameplayStatesBlackboard.GetCurrentPlayer()->GetScore().AddLast();
		m_wellplacedBallsThisTurn.emplace_back(m_blackBall);
		m_gameplayStatesBlackboard.p_victoryAchieved = true;
	}
}

void BilliardsGameplayManager::OnRedBallEnteredHole(BilliardBall* redBall)
{
	if (m_gameplayStatesBlackboard.GetCurrentPlayer() == &m_playerRed)
	{
		m_wellplacedBallsThisTurn.push_back(redBall);
	}

	m_playerRed.RemoveRemainingColoredBall(redBall);

	IncrementPlayerScoreWithThisTurnState();
}

void BilliardsGameplayManager::OnBlueBallEnteredHole(BilliardBall* blueBall)
{
	if (m_gameplayStatesBlackboard.GetCurrentPlayer() == &m_playerBlue)
	{
		m_wellplacedBallsThisTurn.push_back(blueBall);
	}

	m_playerBlue.RemoveRemainingColoredBall(blueBall);

	IncrementPlayerScoreWithThisTurnState();
}

void BilliardsGameplayManager::IncrementPlayerScoreWithThisTurnState()
{
	if (m_wellplacedBallsThisTurn.size() < 2)
	{
		m_gameplayStatesBlackboard.GetCurrentPlayer()->GetScore().Add();
	}
	else
	{
		m_gameplayStatesBlackboard.GetCurrentPlayer()->GetScore().AddConsecutive();
	}
}




const std::vector<BilliardBall*>& BilliardsGameplayManager::GetWellplacedBalls()
{
	return m_wellplacedBallsThisTurn;
}

const std::vector<BilliardBall*>& BilliardsGameplayManager::GetMissplacedBalls()
{
	return m_missplacedBallsThisTurn;
}

void BilliardsGameplayManager::ClearWellplacedBalls()
{
	m_wellplacedBallsThisTurn.clear();
}

void BilliardsGameplayManager::ClearMissplacedBalls()
{
	m_missplacedBallsThisTurn.clear();
}



const Vector2<float> BilliardsGameplayManager::FindRandomValidPositionForBall(BilliardBall* ball) const 
{
	const Vector2<float> randomBounds{ 2.5f, 1.5f };
	const Circle& ballCollisionShape = ball->GetCollisionCircle();

	bool foundValidPosition = false;
	Vector2<float> randomPosition;

	do
	{
		randomPosition =
			m_gameplayStatesBlackboard.GetBoardCenter() +
			GameRandom::GetInstance()->GetRandomVectorBetweenSignedBounds(randomBounds);

		foundValidPosition = Physics2DManager::GetInstance()->CircleOverlap(randomPosition, ballCollisionShape.GetRadius()).size() < 1;


	} while (!foundValidPosition);



	return randomPosition;
}
