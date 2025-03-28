#include "AABoxColliderDrawer.h"


bool AABoxColliderDrawer::s_enabled = true;

AABoxColliderDrawer::AABoxColliderDrawer(const std::shared_ptr<AABoxCollider2D>& aaBoxCollider)
	: m_aaBoxCollider(aaBoxCollider)
{
}

AABoxColliderDrawer::~AABoxColliderDrawer()
{
}

void AABoxColliderDrawer::Update()
{
	if (!s_enabled) return;

	const Rect<float> rect = m_aaBoxCollider->GetShape();
	const Rect<int> drawRect{ GameSpacesComputer::GetInstance()->WorldToWindowRect(rect) };

	GameRenderManager::GetInstance()->DrawDebugRect(Colors::Red, drawRect);
}
