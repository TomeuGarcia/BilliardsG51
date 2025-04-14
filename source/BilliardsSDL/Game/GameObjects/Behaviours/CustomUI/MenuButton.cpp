#include "MenuButton.h"


MenuButton::MenuButton(UIButton* button, const bool& canBeSelectedOnlyOnce, const std::shared_ptr<SFXSound>& selectedSound)
	: m_button(button), m_canBeSelectedOnlyOnce(canBeSelectedOnlyOnce), m_selectedSound(selectedSound),	m_selectedCallback(),
	m_delayToEnd(0.15f), m_buttonScaleBy(0.9f)
{
}

void MenuButton::Start()
{
	m_button->p_onSelectedCallback = std::bind(&MenuButton::DoOnButtonSelectedStart, this);
}

void MenuButton::OnDestroy()
{
	GameDelayedCallScheduler::GetInstance()->RemoveAllCalls(this);
	GameTweener::GetInstance()->CompleteScale(m_button->GetRenderer());
}

GameObject* MenuButton::GetGameObject()
{
	return m_button->GetRenderer()->GetGameObject();
}


void MenuButton::SetSelectedCallback(const std::function<void()>& callback)
{
	m_selectedCallback = callback;
}



void MenuButton::DoOnButtonSelectedStart()
{
	if (m_canBeSelectedOnlyOnce)
	{
		m_button->p_onSelectedCallback = []() {};
	}

	m_selectedSound->Play();	
	GameDelayedCallScheduler::GetInstance()->AddCall(this, m_delayToEnd, std::bind(&MenuButton::DoOnButtonSelectedFinish, this));
	GameTweener::GetInstance()->TweenScaleBy(m_button->GetRenderer(), Vector2<float>::One() * m_buttonScaleBy, 0.05f, 0.0f);
}


void MenuButton::DoOnButtonSelectedFinish()
{
	m_button->GetRenderer()->p_scale /= m_buttonScaleBy;
	m_selectedCallback();
}