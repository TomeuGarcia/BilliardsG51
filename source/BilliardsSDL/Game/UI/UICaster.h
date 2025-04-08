#pragma once
#include <memory>
#include <vector>

#include "../../Shared/Math/Math.h"
#include "../Systems/GameInput.h"

#include "Selectables/UISelectable.h"


class UICaster
{
public:
	UICaster(GameInput* gameInput);
	~UICaster();

	static UICaster* GetInstance();

	void AddSelectable(const std::shared_ptr<UISelectable>& selectable);
	void ClearSelectables();


	void Update(const float& deltaTime);


private:
	void UpdateHovering();
	void UpdateSelecting();

	bool IsSelectableBeingHovered(const UISelectable* selectable);	

	void UpdateSelectables(const float& deltaTime);


private:
	GameInput* m_gameInput;

	std::vector<std::shared_ptr<UISelectable>> m_selectables;
	UISelectable* m_currentlySelectedSelectable;

private:
	static UICaster* s_instance;
};