#include "BilliardsGameplayManager.h"

BilliardsGameplayManager::BilliardsGameplayManager()
	: m_stick(nullptr), m_pinned(false),
	m_playerthinkingFsm()
{
}

BilliardsGameplayManager::~BilliardsGameplayManager()
{
}


void BilliardsGameplayManager::Init(BilliardStick * stick)
{
	m_stick = stick;

	m_playerthinkingFsm.Init();
	m_playerthinkingFsm.Enter();

}



void BilliardsGameplayManager::Update()
{
	if (m_playerthinkingFsm.Update())
	{
		m_playerthinkingFsm.Exit();
		m_playerthinkingFsm.Enter(); // for now
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
