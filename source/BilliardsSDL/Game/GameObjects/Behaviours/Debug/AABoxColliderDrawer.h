#pragma once
#include "../Behaviour.h"
#include "../../../Physics/Colliders/AABoxCollider2D.h"
#include "../../../Render/GameRenderManager.h"
#include "../../../Systems/GameSpacesComputer.h"


class AABoxColliderDrawer : public Behaviour
{
public:
	AABoxColliderDrawer(const std::shared_ptr<AABoxCollider2D>& aaBoxCollider);
	~AABoxColliderDrawer();

	virtual void Update() override;


private:
	std::shared_ptr<AABoxCollider2D> m_aaBoxCollider;
};