#include "CircleColliderDrawer.h"


bool CircleColliderDrawer::s_enabled = true;

CircleColliderDrawer::CircleColliderDrawer(const std::shared_ptr<CircleCollider2D>& circleCollider)
	: m_circleCollider(circleCollider)
{
	
}

CircleColliderDrawer::~CircleColliderDrawer()
{
}

void CircleColliderDrawer::Update()
{
	if (!s_enabled) return;

	const Circle circle = m_circleCollider->GetShape();

	std::vector<Vector2<int>> octagonalPositions(9);
	float rotationStep = 360.0f / (octagonalPositions.size() - 1);
	Vector2<float> direction = Vector2<float>::Up();

	for (size_t i = 0; i < octagonalPositions.size() - 1; ++i)
	{
		Vector2<float> position = circle.p_position + (direction * circle.GetRadius());
		octagonalPositions[i] = GameSpacesComputer::GetInstance()->WorldToWindowPosition(position);

		direction = Math::Rotate(direction, rotationStep);
	}
	octagonalPositions[octagonalPositions.size() - 1] = octagonalPositions[0];

	GameRenderManager::GetInstance()->DrawDebugLines(Colors::Green, octagonalPositions);
}
