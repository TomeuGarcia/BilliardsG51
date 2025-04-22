#include "TestBehaviour.h"

TestBehaviour::TestBehaviour(const std::shared_ptr<Image>& image, const std::shared_ptr<Text>& text)
	: m_image(image), m_text(text)
{
}

TestBehaviour::~TestBehaviour()
{
}

void TestBehaviour::Update()
{
	const float time{ GameTime::GetInstance()->GetTime() };
	m_image->SetRotation(time * 50.0f);


	const float t{ fmod(time, 1.0f) };
	Color textColor = Color::Lerp(Colors::SoftBlue, Colors::SoftGreen, t);
	m_text->SetColorTint(textColor);
}
