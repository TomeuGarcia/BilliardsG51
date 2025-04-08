#include "UICaster.h"


UICaster* UICaster::s_instance = nullptr;

UICaster::UICaster(GameInput* gameInput)
	: m_gameInput(gameInput),
	m_selectables(), m_currentlySelectedSelectable(nullptr)
{
	m_selectables.reserve(10);
	s_instance = this;
}

UICaster::~UICaster()
{
	s_instance = nullptr;
}


UICaster* UICaster::GetInstance()
{
	return s_instance;
}



void UICaster::AddSelectable(const std::shared_ptr<UISelectable>& selectable)
{
	m_selectables.emplace_back(selectable);
}

void UICaster::ClearSelectables()
{
	m_selectables.clear();
}


void UICaster::Update(const float& deltaTime)
{
	if (m_gameInput->GetKeyDown(KeyCode::MouseLeft))
	{
		UpdateSelecting();
	}
	else
	{
		UpdateHovering();
	}

	UpdateSelectables(deltaTime);
}



void UICaster::UpdateHovering()
{
	size_t i = 0;
	for (; i < m_selectables.size(); ++i)
	{
		UISelectable* selectable = m_selectables[i].get();
		const bool isBeingHovered = IsSelectableBeingHovered(selectable);
		selectable->SetHoveredState(isBeingHovered);

		if (isBeingHovered) 
		{ 
			++i;
			break; 
		}
	}

	for (; i < m_selectables.size(); ++i)
	{
		m_selectables[i]->SetHoveredState(false);
	}
}

void UICaster::UpdateSelecting()
{
	for (size_t i = 0; i < m_selectables.size(); ++i)
	{
		UISelectable* selectable = m_selectables[i].get();
		if (IsSelectableBeingHovered(selectable))
		{
			selectable->SetSelectedState();
			return;
		}
	}
}



bool UICaster::IsSelectableBeingHovered(const UISelectable* selectable)
{
	return Math::IsPointInsideRect(selectable->GetWindowBounds(), m_gameInput->GetMouseWindowPosition());
}


void UICaster::UpdateSelectables(const float& deltaTime)
{
	for (auto it = m_selectables.begin(); it < m_selectables.end(); ++it)
	{
		(*it)->Update(deltaTime);
	}
}
