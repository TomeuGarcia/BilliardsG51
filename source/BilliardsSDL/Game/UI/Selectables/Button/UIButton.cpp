#include "UIButton.h"

UIButton::UIButton(const std::shared_ptr<Renderer>& renderer, const ColorBlock& colorBlock)
	: m_renderer(renderer), m_colorBlock(colorBlock),
	m_goalColorTimer(0.15f), m_previousColor(colorBlock.p_normalColor), m_goalColor(colorBlock.p_normalColor)
{
}


Rect<int> UIButton::GetWindowBounds() const
{
	return m_renderer->GetDestinationRect();
}


void UIButton::Update(const float& deltaTime)
{
	m_goalColorTimer.Update(deltaTime);
	m_renderer->SetColorTint(Color::Lerp(m_previousColor, m_goalColor, m_goalColorTimer.GetRatio01()));
}


void UIButton::OnUnhovered()
{
	UpdateGoalColor(m_colorBlock.p_normalColor);
	printf("Unhovered\n");
}

void UIButton::OnHovered()
{
	UpdateGoalColor(m_colorBlock.p_hoveredColor);
	printf("Hovered\n");
}

void UIButton::OnSelected()
{
	UpdateGoalColor(m_colorBlock.p_selectedColor);
	printf("Selected\n");
}

void UIButton::UpdateGoalColor(const Color& goalColor)
{
	m_goalColorTimer.ClearTime();
	m_previousColor = m_goalColor;
	m_goalColor = goalColor;
}
