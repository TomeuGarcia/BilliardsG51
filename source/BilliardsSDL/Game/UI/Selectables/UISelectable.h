#pragma once
#include "../../../Shared/Types/Rect/Rect.h"


class UISelectable
{
private:
	enum class State
	{
		Unhovered, 
		Hovered,
		JustSelected,
		Selected
	};


public:
	UISelectable();

	void SetHoveredState(const bool& isBeingHovered);
	void SetSelectedState();

	virtual Rect<int> GetWindowBounds() const = 0;
	virtual bool IsActive() const = 0;

	virtual void Update(const float& deltaTime) = 0;

	virtual void WhenNotActiveUpdate() = 0;

protected:
	virtual void OnUnhovered() = 0;
	virtual void OnHovered() = 0;
	virtual void OnSelected() = 0;


private:
	State m_state;
};