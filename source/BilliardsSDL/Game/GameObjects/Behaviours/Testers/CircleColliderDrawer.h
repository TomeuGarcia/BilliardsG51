#pragma once
#include "../Behaviour.h"
#include "../../../Physics/Colliders/CircleCollider2D.h"
#include "../../../Render/GameRenderManager.h"
#include "../../../Systems/GameSpacesComputer.h"


class CircleColliderDrawer : public Behaviour
{
public:
	CircleColliderDrawer(const std::shared_ptr<CircleCollider2D>& circleCollider);
	~CircleColliderDrawer();

	virtual void Update() override;


public:
	static bool s_enabled;

private:
	std::shared_ptr<CircleCollider2D> m_circleCollider;
};

