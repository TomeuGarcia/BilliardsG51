#include "UISelectable.h"

UISelectable::UISelectable()
	: m_state(State::Unhovered)
{
}

void UISelectable::SetHoveredState(const bool& isBeingHovered)
{
	if (m_state == State::JustSelected && isBeingHovered)
	{
		m_state = State::Selected;
	}
	else if (m_state == State::Unhovered && isBeingHovered)
	{
		m_state = State::Hovered;
		OnHovered();
	}
	else if (m_state != State::Unhovered && !isBeingHovered)
	{
		m_state = State::Unhovered;
		OnUnhovered();
	}
}

void UISelectable::SetSelectedState()
{
	m_state = State::JustSelected;
	OnSelected();
}
