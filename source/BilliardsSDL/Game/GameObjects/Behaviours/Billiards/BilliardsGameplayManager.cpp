#include "BilliardsGameplayManager.h"

BilliardsGameplayManager::BilliardsGameplayManager(const BilliardsScore::Configuration& scoreConfiguration)
	: 
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


	m_gameplayStatesBlackboard.Init(balls, m_whiteBall, boardCenter, &m_playerRed, &m_playerBlue, this);
}


void BilliardsGameplayManager::OnDestroy()
{
	m_scoresDisplay->Cleanup();
}


BilliardsGameplayStateBlackboard* BilliardsGameplayManager::GetBlackboard()
{
	return &m_gameplayStatesBlackboard;
}




bool BilliardsGameplayManager::CanHitWhiteBall(const Vector2<float>& position)
{
	const Circle probingCircle{ position, 0.2f };
	bool intersecting = Math::AreCirclesIntersecting(probingCircle, m_whiteBall->GetCollisionCircle());
	return intersecting;
}

void BilliardsGameplayManager::HitWhiteBall(const Vector2<float>& direction, const float& forceMagnitude)
{
	const Vector2<float> force = direction * forceMagnitude;
	m_whiteBall->ApplyForce(force);
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



void BilliardsGameplayManager::OnBallExitsBoardBounds(BilliardBall* ball)
{
	m_missplacedBallsThisTurn.emplace_back(ball);
	ball->SetIgnoringPhysics();
}



void BilliardsGameplayManager::OnAnyBallEnteredHole(BilliardBall* ball, const Vector2<float>& holeCenter)
{
	ball->PlayEnterEnterHoleAnimation(holeCenter);
	ball->SetIgnoringPhysics();	
	m_feedbackDisplay->PlayAnyBallEnterHole();
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
	const Vector2<float> randomBounds{ 2.5f, 1.75f };
	BilliardsUtilities::PositionBallsRandomly(m_gameplayStatesBlackboard.GetBalls(), 
		m_gameplayStatesBlackboard.GetBoardCenter(), randomBounds);
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