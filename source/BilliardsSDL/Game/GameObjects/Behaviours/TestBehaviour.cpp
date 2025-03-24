#include "TestBehaviour.h"

TestBehaviour::TestBehaviour(const std::shared_ptr<Image>& image)
	: m_image(image)
{
}

TestBehaviour::~TestBehaviour()
{
}

void TestBehaviour::Update()
{
	m_image->p_rotationInDegrees = GameTime::GetInstance()->GetTime() * 50.0f;
}
