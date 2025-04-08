#include "UIButton.h"

UIButton::UIButton(const std::shared_ptr<Renderer>& renderer, const ColorBlock& colorBlock)
	: m_renderer(renderer), m_colorBlock(colorBlock),
	m_goalColorTimer(0.15f), m_previousColor(colorBlock.p_normalColor), m_goalColor(colorBlock.p_normalColor),
	p_onSelectedCallback([](){}),
	p_onHoveredCallback([](){})
{
}


Rect<int> UIButton::GetWindowBounds() const
{
	return m_renderer->GetDestinationRect();
}

bool UIButton::IsActive() const
{
	return m_renderer->IsActive();
}


void UIButton::Update(const float& deltaTime)
{
	m_goalColorTimer.Update(deltaTime);
	m_renderer->SetColorTint(Color::Lerp(m_previousColor, m_goalColor, m_goalColorTimer.GetRatio01()));
}


void UIButton::OnUnhovered()
{
	UpdateGoalColor(m_colorBlock.p_normalColor, m_previousColor);
}

void UIButton::OnHovered()
{
	UpdateGoalColor(m_colorBlock.p_hoveredColor, m_previousColor);
	p_onHoveredCallback();
}

void UIButton::OnSelected()
{
	UpdateGoalColor(m_previousColor, m_colorBlock.p_selectedColor);
	p_onSelectedCallback();
}

void UIButton::UpdateGoalColor(const Color& goalColor, const Color& currentColor)
{
	m_goalColorTimer.ClearTime();
	m_previousColor = m_goalColor;
	m_goalColor = goalColor;
}
