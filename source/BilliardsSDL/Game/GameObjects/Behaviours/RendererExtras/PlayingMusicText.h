#pragma once
#include "../Behaviour.h"
#include "../../../Render/Renderers/Text/Text.h"

#include "../../../Audio/MusicService/GameMusicService.h"

#include "../../../Scenes/Utilities/SceneCreateUtilities.h"


class PlayingMusicText : public Behaviour
{
public:
	struct Config
	{
		std::string prefix;
		std::string suffix;

		int pointSize;
		const TextResourceData* textFontData;

		float fadeDelay;
		float fadeDuration;
	};

public:
	PlayingMusicText(GameObject* gameObject, const GameMusicService::MusicType& music, const Config& config, 
		SceneCreateUtilities* createUtilities);

	virtual void OnDestroy() override;


private:
	Text* m_text;
};