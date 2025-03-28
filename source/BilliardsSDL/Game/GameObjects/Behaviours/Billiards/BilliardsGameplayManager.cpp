#include "BilliardsGameplayManager.h"

BilliardsGameplayManager::BilliardsGameplayManager()
	: m_stick(nullptr), m_pinned(false),
	m_gameplayStatesMap(),
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
	m_playerRed.Init(redStick);
	m_playerBlue.Init(blueStick);
	m_gameplayStatesBlackboard.Init(balls, boardCenter, &m_playerRed, &m_playerBlue);

	m_gameplayStatesMap[BilliardsGameplayState::Type::Init] = 
			  std::make_shared<BilliardsGameplayState_Init>(&m_gameplayStatesBlackboard);
	m_gameplayStatesMap[BilliardsGameplayState::Type::PlacingBalls] = 
			  std::make_shared<BilliardsGameplayState_PlacingBalls>(&m_gameplayStatesBlackboard);
	m_gameplayStatesMap[BilliardsGameplayState::Type::Thinking_Red] = 
			  std::make_shared<BilliardsGameplayState_PlayerThinking>(&m_gameplayStatesBlackboard, &m_playerRed);
	m_gameplayStatesMap[BilliardsGameplayState::Type::Thinking_Blue] = 
			  std::make_shared<BilliardsGameplayState_PlayerThinking>(&m_gameplayStatesBlackboard, &m_playerBlue);
	m_gameplayStatesMap[BilliardsGameplayState::Type::GameFinish] = 
			  std::make_shared<BilliardsGameplayState_GameFinish>(&m_gameplayStatesBlackboard);

	m_currentState = (m_gameplayStatesMap[BilliardsGameplayState::Type::Init]).get();
	m_currentState->Enter();


	 
	m_stick = redStick;
}



void BilliardsGameplayManager::Update()
{
	if (m_currentState->Update())
	{
		m_currentState->Exit();
		m_currentState = (m_gameplayStatesMap[m_currentState->GetNextState()]).get();
		m_currentState->Enter();
	}


	Vector2<float> currentMousePosition = GameInput::GetInstance()->GetMouseWorldPosition();
	if (GameInput::GetInstance()->GetKeyDown(KeyCode::MouseLeft))
	{
		m_pinned = true;
		m_pinPosition = currentMousePosition;
	}
	if (GameInput::GetInstance()->GetKeyUp(KeyCode::MouseLeft))
	{
		m_pinned = false;
	}


	if (m_pinned)
	{
		Vector2<float> currentToPin = m_pinPosition - currentMousePosition;
		float currentToPinDistance = currentToPin.Length();
		Vector2<float> currentToPinDirection = currentToPinDistance < 0.01f ? Vector2<float>::Up() : (currentToPin / currentToPinDistance);

		Vector2<float> lookDirection = currentToPinDirection;

		Vector2<float> tipPosition = m_pinPosition;

		float m_maxPinDragDistance = 2.0f;
		float pinDragDistance = Math::Min(m_maxPinDragDistance, currentToPinDistance);

		tipPosition -= currentToPinDirection * pinDragDistance;


		m_stick->SetTipPositionAndLookDirection(tipPosition, lookDirection);


		GameRenderManager::GetInstance()->DrawDebugLine(
			Colors::Yellow, GameSpacesComputer::GetInstance()->WorldToWindowLine(Line<float>(m_pinPosition, tipPosition))
		);

	}
	else
	{
		m_stick->SetTipPositionAndLookDirection(currentMousePosition, Vector2<float>::Up());
	}



}
