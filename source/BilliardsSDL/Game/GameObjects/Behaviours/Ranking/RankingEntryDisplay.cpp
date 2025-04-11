#include "RankingEntryDisplay.h"

RankingEntryDisplay::RankingEntryDisplay(GameObject* gameObject, const int& i, Text* placingText, Text* scoreText, Text* nameText)
	: m_gameObject(gameObject), m_index(i),
	m_placingText(placingText), m_scoreText(scoreText), m_nameText(nameText),
	m_appearSound()
{
}


void RankingEntryDisplay::Start()
{
	const Vector2<float> centerPosition = m_gameObject->GetTransform()->p_worldPosition;

	m_scoreText->GetTransform()->p_worldPosition =		centerPosition + Vector2<float>(-1.75f, 0.0f);
	m_placingText->GetTransform()->p_worldPosition =	centerPosition + Vector2<float>(-0.25f, 0.0f);
	m_nameText->GetTransform()->p_worldPosition =		centerPosition + Vector2<float>(1.75f, 0.0f);

	const Color textColor = m_scoreText->GetColorTint();
	m_scoreText->SetColorTint(textColor.WithAlpha(0));

	const Color placingColor = m_placingText->GetColorTint();
	m_placingText->SetColorTint(placingColor.WithAlpha(0));

	const Color nameColor = m_nameText->GetColorTint();
	m_nameText->SetColorTint(nameColor.WithAlpha(0));


	const float appearDelay = (m_index + 1) * 0.2f;
	const float appearDuration = 0.2f;

	GameTweener::GetInstance()->TweenColor(m_scoreText,		textColor, appearDuration, appearDelay);
	GameTweener::GetInstance()->TweenColor(m_placingText,	placingColor, appearDuration, appearDelay + 0.05f);
	GameTweener::GetInstance()->TweenColor(m_nameText,		nameColor, appearDuration, appearDelay + 0.10f);


	m_appearSound = GameAudioManager::GetInstance()->CreateSFXSound(GameAssetResources::GetInstance()->GetAudio().textAppearSoundData);
	GameDelayedCallScheduler::GetInstance()->AddCall(this, appearDelay, std::bind(&RankingEntryDisplay::PlayAppearSound, this));
}

void RankingEntryDisplay::OnDestroy()
{
	GameDelayedCallScheduler::GetInstance()->RemoveAllCalls(this);
}


void RankingEntryDisplay::PlayAppearSound()
{
	m_appearSound->Play();
}
