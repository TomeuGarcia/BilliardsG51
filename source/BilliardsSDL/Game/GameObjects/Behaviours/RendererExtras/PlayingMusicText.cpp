#include "PlayingMusicText.h"

PlayingMusicText::PlayingMusicText(GameObject* gameObject, const GameMusicService::MusicType& music, const Config& config, 
	SceneCreateUtilities* createUtilities)
	: m_text(nullptr)
{
	std::string text = config.prefix + std::string(GameMusicService::GetInstance()->GetMusicAuthorAndName(music)) + config.suffix;
	m_text = createUtilities->CreateTextComponent(gameObject, *config.textFontData, text, config.pointSize).get();

	GameTweener::GetInstance()->TweenColor(m_text, Colors::TransparentWhite, config.fadeDuration, config.fadeDelay);
}

void PlayingMusicText::OnDestroy()
{
	GameTweener::GetInstance()->CompleteColor(m_text);
}
