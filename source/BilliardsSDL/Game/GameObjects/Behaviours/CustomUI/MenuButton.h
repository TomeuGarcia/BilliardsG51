#pragma once
#include "../Behaviour.h"
#include "../../GameObject.h"
#include "../../../UI/Selectables/Button/UIButton.h"
#include "../../../Audio/SFXSound.h"
#include "../../../Systems/GameDelayedCallScheduler.h"
#include "../../../Systems/GameTweener.h"


class MenuButton : public Behaviour, public GameDelayedCallScheduler::ICallSource
{
public:
	MenuButton(UIButton* button, const bool& canBeSelectedOnlyOnce, const std::shared_ptr<SFXSound>& selectedSound);

	virtual void Start() override;
	virtual void OnDestroy() override;

	GameObject* GetGameObject();

	void SetSelectedCallback(const std::function<void()>& callback);


private:
	void DoOnButtonSelectedStart();
	void DoOnButtonSelectedFinish();


private:
	UIButton* m_button;
	bool m_canBeSelectedOnlyOnce;
	std::shared_ptr<SFXSound> m_selectedSound;

	std::function<void()> m_selectedCallback;

	float m_delayToEnd;
	float m_buttonScaleBy;
};