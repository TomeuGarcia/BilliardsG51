#include "BilliardsGameplayManager.h"

BilliardsGameplayManager::BilliardsGameplayManager()
	: m_gameplayStatesMap(),
	m_currentState(nullptr),
	m_gameplayStatesBlackboard(),
	m_playerRed(),
	m_playerBlue()
{
}

BilliardsGameplayManager::~BilliardsGameplayManager()
{
}


void BilliardsGameplayManager::Init(const std::vector<BilliardBall*>& balls, const Vector2<float>& boardCenter, 
	BilliardStick* redStick, BilliardStick* blueStick)
{
	m_playerRed.Init(redStick, Colors::SoftRed);
	m_playerBlue.Init(blueStick, Colors::SoftBlue);
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
}

void BilliardsGameplayManager::OnDestroy()
{
	m_currentState->Exit();
}




bool BilliardsGameplayManager::TryHitBalls(const Vector2<float>& position, const Vector2<float>& direction,
	const float& forceMagnitude)
{
	const Vector2<float> force = direction * forceMagnitude;

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
}



