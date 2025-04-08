#pragma once
#include "../UISelectable.h"
#include "../ColorBlock.h"
#include "../../../Render/Renderers/Renderer.h"
#include "../../../../Shared/Timer/Timer.h"


class UIButton : public UISelectable
{
public:
	UIButton(const std::shared_ptr<Renderer>& renderer, const ColorBlock& colorBlock);

	Rect<int> GetWindowBounds() const override;

	void Update(const float& deltaTime) override;

	void OnUnhovered() override;
	void OnHovered() override;
	void OnSelected() override;


private:
	void UpdateGoalColor(const Color& goalColor);


private:
	std::shared_ptr<Renderer> m_renderer;
	ColorBlock m_colorBlock;

	Timer m_goalColorTimer;
	Color m_previousColor;
	Color m_goalColor;
};