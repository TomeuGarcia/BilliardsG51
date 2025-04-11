#pragma once

#include "../Behaviour.h"
#include "../../../Render/Renderers/Text/Text.h"

#include "../../../Systems/GameTweener.h"

#include "../../../Audio/GameAudioManager.h"
#include "../../../../Shared/Timer/Timer.h"
#include "../../../Systems/GameAssetResources.h"
#include "../../../Systems/GameTime.h"

#include "../../../Systems/GameDelayedCallScheduler.h"


class RankingEntryDisplay : public Behaviour, public GameDelayedCallScheduler::ICallSource
{
public:
	RankingEntryDisplay(GameObject* gameObject, const int& i,
		Text* placingText, Text* scoreText, Text* nameText);

	virtual void Start() override;
	virtual void OnDestroy() override;

private:
	void PlayAppearSound();


private:
	GameObject* m_gameObject;
	int m_index;

	Text* m_placingText;
	Text* m_scoreText;
	Text* m_nameText;

	std::shared_ptr<SFXSound> m_appearSound;
};
