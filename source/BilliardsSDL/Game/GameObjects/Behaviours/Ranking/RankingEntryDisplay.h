#pragma once

#include "../Behaviour.h"
#include "../../../Render/Renderers/Text/Text.h"

#include "../../../Systems/GameTweener.h"


class RankingEntryDisplay : public Behaviour
{
public:
	RankingEntryDisplay(GameObject* gameObject, const int& i,
		Text* placingText, Text* scoreText, Text* nameText);

	virtual void Start() override;


private:
	GameObject* m_gameObject;
	int m_index;

	Text* m_placingText;
	Text* m_scoreText;
	Text* m_nameText;
};
