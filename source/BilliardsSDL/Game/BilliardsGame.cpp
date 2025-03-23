#include "BilliardsGame.h"

BilliardsGame::BilliardsGame()
	: p_quitApplication(false), m_systems()
{
}

BilliardsGame::~BilliardsGame()
{
}

void BilliardsGame::Init(const GameSystems& systems)
{
	m_systems = systems;
}

void BilliardsGame::Cleanup()
{

}


void BilliardsGame::Update()
{
	if (m_systems.GetInputState()->GetKeyDown(KeyCode::MouseLeft))
	{
		printf("Click\n");
	}
	else if (m_systems.GetInputState()->GetKey(KeyCode::MouseLeft))
	{
		const Vector2<int> windowSize{ m_systems.GetRenderManager()->GetWindowSize() };
		m_systems.GetRenderManager()->DrawLine(Colors::Red, Vector2<int>{ 50, 50 }, windowSize - Vector2<int>{ 50, 50 });
	}	
}

void BilliardsGame::Render() const
{

}
