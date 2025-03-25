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

	const Vector2<int> drawRectPosition = GameSpacesComputer::GetInstance()->WorldToWindowPosition(Vector2<float>(rect.x, rect.y));
	const Vector2<int> drawRectSize = GameSpacesComputer::GetInstance()->WorldToWindowVector(Vector2<float>(rect.width, rect.height));
	const Rect<int> drawRect{ drawRectPosition, drawRectSize };

	GameRenderManager::GetInstance()->DrawDebugRect(Colors::Red, drawRect);
}
