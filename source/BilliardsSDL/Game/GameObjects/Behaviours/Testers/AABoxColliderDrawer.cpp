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

	GameRenderManager::GetInstance()->DrawGizmoRect(Colors::Red, m_aaBoxCollider->GetShape());
}
