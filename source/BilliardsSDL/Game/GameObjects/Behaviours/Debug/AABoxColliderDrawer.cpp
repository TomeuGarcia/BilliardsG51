#include "AABoxColliderDrawer.h"

AABoxColliderDrawer::AABoxColliderDrawer(const std::shared_ptr<AABoxCollider2D>& aaBoxCollider)
	: m_aaBoxCollider(aaBoxCollider)
{
}

AABoxColliderDrawer::~AABoxColliderDrawer()
{
}

void AABoxColliderDrawer::Update()
{
	const Rect<float> rect = m_aaBoxCollider->GetShape();
	const Rect<int> drawRect{ GameSpacesComputer::GetInstance()->WorldToWindowRect(rect) };

	GameRenderManager::GetInstance()->DrawDebugRect(Colors::Red, drawRect);
}
