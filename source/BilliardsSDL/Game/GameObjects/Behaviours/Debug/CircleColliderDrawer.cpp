#include "CircleColliderDrawer.h"

CircleColliderDrawer::CircleColliderDrawer(const std::shared_ptr<CircleCollider2D>& circleCollider)
	: m_circleCollider(circleCollider)
{
	
}

CircleColliderDrawer::~CircleColliderDrawer()
{
}

void CircleColliderDrawer::Update()
{
	const Circle circle = m_circleCollider->GetShape();

	const Rect<int> drawRect{ GameSpacesComputer::GetInstance()->WorldToWindowRect(circle.MakeAARect()) };

	GameRenderManager::GetInstance()->DrawDebugRect(Colors::Green, drawRect);
}
