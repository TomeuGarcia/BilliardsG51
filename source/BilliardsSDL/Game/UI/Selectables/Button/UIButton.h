#pragma once
#include <functional>

#include "../UISelectable.h"
#include "../ColorBlock.h"
#include "../../../Render/Renderers/Renderer.h"
#include "../../../../Shared/Timer/Timer.h"


class UIButton : public UISelectable
{
public:
	UIButton(const std::shared_ptr<Renderer>& renderer, const ColorBlock& colorBlock);

	virtual Rect<int> GetWindowBounds() const override;
	virtual bool IsActive() const override;

	virtual void Update(const float& deltaTime) override;

	virtual void OnUnhovered() override;
	virtual void OnHovered() override;
	virtual void OnSelected() override;


private:
	void UpdateGoalColor(const Color& goalColor, const Color& currentColor);


public:
	std::function<void()> p_onSelectedCallback;
	std::function<void()> p_onHoveredCallback;

private:
	std::shared_ptr<Renderer> m_renderer;
	ColorBlock m_colorBlock;

	Timer m_goalColorTimer;
	Color m_previousColor;
	Color m_goalColor;
};