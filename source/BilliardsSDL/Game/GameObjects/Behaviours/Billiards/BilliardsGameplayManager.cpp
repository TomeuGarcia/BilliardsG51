#include "BilliardsGameplayManager.h"

BilliardsGameplayManager::BilliardsGameplayManager(const BilliardsScore::Configuration& scoreConfiguration)
	: m_gameplayStatesMap(),
	m_currentState(nullptr),
	m_gameplayStatesBlackboard(),
	m_playerRed(scoreConfiguration),
	m_playerBlue(scoreConfiguration),
	m_wellplacedBallsThisTurn(),
	m_missplacedBallsThisTurn(),
	m_blackBallWellPlaced(false),
	m_blackBall(nullptr), m_whiteBall(nullptr),
	m_feedbackDisplay(nullptr), m_scoresDisplay(nullptr)
{
	m_wellplacedBallsThisTurn.reserve(5);
	m_missplacedBallsThisTurn.reserve(2);
}

BilliardsGameplayManager::~BilliardsGameplayManager()
{
}

void BilliardsGameplayManager::Init(const std::vector<BilliardBall*>& balls, const Vector2<float>& boardCenter, 
	BilliardStick* redStick, BilliardStick* blueStick, 
	const std::shared_ptr<BilliardsGameplayFeedbackDisplay>& feedbackDisplay, 
	const std::shared_ptr<IPlayerScoresDisplay>& scoresDisplay)
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

	m_playerRed.Init(redStick, Colors::SoftRed, remainingRedBalls, "Player Red");
	m_playerBlue.Init(blueStick, Colors::SoftBlue, remainingBlueBalls, "Player Blue");


	m_feedbackDisplay = feedbackDisplay;

	m_scoresDisplay = scoresDisplay;
	m_scoresDisplay->Init({ &m_playerRed, &m_playerBlue });
	m_scoresDisplay->UpdateDisplayedScore();


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
}




void BilliardsGameplayManager::Start()
{
	m_currentState = (m_gameplayStatesMap[BilliardsGameplayState::Type::Init]).get();
	m_currentState->Enter();
}

void BilliardsGameplayManager::Update()
{
	if (GameInput::GetInstance()->GetKeyDown(KeyCode::Esc))
	{
		SceneManager::GetInstance()->LoadScene(SceneName::MainMenu);
		return;
	}

	if (m_currentState->Update())
	{
		m_currentState->Exit();
		
		const BilliardsGameplayState::Type nextState = m_currentState->GetNextState();
		if (nextState == BilliardsGameplayState::Type::GameQuit)
		{
			SceneManager::GetInstance()->LoadScene(SceneName::MainMenu);
			return;
		}

		m_currentState = (m_gameplayStatesMap[nextState]).get();
		m_currentState->Enter();
	}
}

void BilliardsGameplayManager::OnDestroy()
{
	m_currentState->Exit();
	m_scoresDisplay->Cleanup();
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



void BilliardsGameplayManager::OnBallEnteredHole(BilliardBall* ball, const Vector2<float>& holeCenter)
{
	OnAnyBallEnteredHole(ball, holeCenter);

	switch (ball->GetColorType())
	{
	case BilliardBall::ColorType::White:
		OnWhiteBallEnteredHole(holeCenter);
		break;
	case BilliardBall::ColorType::Black:
		OnBlackBallEnteredHole(holeCenter);
		break;
	case BilliardBall::ColorType::Red:
		OnRedBallEnteredHole(ball, holeCenter);
		break;
	case BilliardBall::ColorType::Blue:
		OnBlueBallEnteredHole(ball, holeCenter);
		break;
	default:
		break;
	}
}



void BilliardsGameplayManager::OnAnyBallEnteredHole(BilliardBall* ball, const Vector2<float>& holeCenter)
{
	ball->PlayEnterEnterHoleAnimation(holeCenter);
	ball->SetIgnoringPhysics();	
}


void BilliardsGameplayManager::OnWhiteBallEnteredHole(const Vector2<float>& holeCenter)
{
	m_missplacedBallsThisTurn.emplace_back(m_whiteBall);
	m_feedbackDisplay->PlayWhiteBallEnterHole(holeCenter);
}

void BilliardsGameplayManager::OnBlackBallEnteredHole(const Vector2<float>& holeCenter)
{
	BilliardsPlayer* currentPlayer = m_gameplayStatesBlackboard.GetCurrentPlayer();
	if (currentPlayer->StillHasRemainingColoredBalls())
	{
		m_missplacedBallsThisTurn.emplace_back(m_blackBall);
		m_feedbackDisplay->PlayBlackBallEnterHole(holeCenter);
	}
	else
	{
		currentPlayer->GetScore().AddLast();
		m_wellplacedBallsThisTurn.emplace_back(m_blackBall);
		m_gameplayStatesBlackboard.p_victoryAchieved = true;
		m_feedbackDisplay->PlayBallEnterHoleScoreLast(holeCenter);
		OnScoreChanged();
	}
}

void BilliardsGameplayManager::OnRedBallEnteredHole(BilliardBall* redBall, const Vector2<float>& holeCenter)
{
	OnPlayerBallEnteredHole(redBall, holeCenter, &m_playerRed);
}

void BilliardsGameplayManager::OnBlueBallEnteredHole(BilliardBall* blueBall, const Vector2<float>& holeCenter)
{
	OnPlayerBallEnteredHole(blueBall, holeCenter, &m_playerBlue);
}

void BilliardsGameplayManager::OnPlayerBallEnteredHole(BilliardBall* ball, const Vector2<float>& holeCenter, BilliardsPlayer* ballOwnerPlayer)
{
	if (m_gameplayStatesBlackboard.GetCurrentPlayer() == ballOwnerPlayer)
	{
		m_wellplacedBallsThisTurn.push_back(ball);
		IncrementPlayerScoreWithThisTurnState(holeCenter);
	}
	else
	{
		BilliardsPlayer* otherPlayer = m_gameplayStatesBlackboard.GetOtherPlayer();
		m_feedbackDisplay->PlayWrongBallEnterHole(holeCenter, otherPlayer->GetBackgroundColor());
		otherPlayer->GetScore().AddByOtherPlayer();
	}

	ballOwnerPlayer->RemoveRemainingColoredBall(ball);
	OnScoreChanged();
}

void BilliardsGameplayManager::IncrementPlayerScoreWithThisTurnState(const Vector2<float>& holeCenter)
{
	BilliardsPlayer* currentPlayer = m_gameplayStatesBlackboard.GetCurrentPlayer();

	if (m_wellplacedBallsThisTurn.size() <= 1)
	{
		currentPlayer->GetScore().Add();
		m_feedbackDisplay->PlayBallEnterHoleScore(holeCenter);
	}
	else
	{
		currentPlayer->GetScore().AddConsecutive();
		m_feedbackDisplay->PlayBallEnterHoleScoreConsecutive(holeCenter);
	}
}

void BilliardsGameplayManager::OnScoreChanged()
{
	m_scoresDisplay->UpdateDisplayedScore();
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



void BilliardsGameplayManager::OnPlayerStartsPlaying()
{
	m_feedbackDisplay->PlayPlayerChange();
}

void BilliardsGameplayManager::OnGameFinishStart()
{
	m_feedbackDisplay->PlayVictory(m_gameplayStatesBlackboard.GetWinnerPlayer()->GetBackgroundColor());
}




void BilliardsGameplayManager::PositionBallsRandomly() const
{
	const Vector2<float> randomBounds{ 1.0f, 0.75f };
	const std::vector<BilliardBall*>& balls = m_gameplayStatesBlackboard.GetBalls();
	const float checkRadius = 0.5f;

	for (auto it = balls.begin(); it != balls.end(); ++it)
	{
		Vector2<float> position = 
			GamePhysicsUtilities::FindRandomPositionWithoutObstacles(m_gameplayStatesBlackboard.GetBoardCenter(), randomBounds,
				checkRadius, 5);

		(*it)->SetPosition(position);
	}
}

const Vector2<float> BilliardsGameplayManager::FindRandomValidPositionForBall(BilliardBall* ball) const
{
	const Vector2<float> randomBounds{ 1.0f, 0.75f };
	const float checkRadius = 0.5f;

	return GamePhysicsUtilities::FindRandomPositionWithoutObstacles(m_gameplayStatesBlackboard.GetBoardCenter(), randomBounds,
		ball->GetCollisionCircle().GetRadius(), 5);
}



void BilliardsGameplayManager::AskWinnerNameAndAddToRanking(BilliardsPlayer* winnerPlayer)
{
	std::printf("\nEnter winner's name: ");

	std::string playerRealName;
	std::cin >> playerRealName;

	RankingEntry rankingEntry{ playerRealName , winnerPlayer->GetScore().GetCurrentValue() };

	RankingManager rankingManager{};
	rankingManager.Load();
	rankingManager.TryAddRankingEntry(rankingEntry);
	rankingManager.Save();
}