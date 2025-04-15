#pragma once
#include "../Behaviour.h"
#include "../../GameObjectGroup.h"
#include "../../../Render/Renderers/Text/Text.h"

#include "../../../Scenes/Utilities/SceneCreateUtilities.h"

#include "../../../../Shared/Math/Math.h"



class TrippyText : public Behaviour
{
public:
	struct Config
	{
		int textPointSize;
		const TextResourceData* textFontData;

		int numberOfTexts;
		float textsTimeOffset;
		
		float rotationSpeed;
		float maxRotation;

		Color frontmostColor;
		Color frontColor;
		Color backColor1;
		Color backColor2;
	};


public:
	TrippyText(GameObject* gameObject, const Config& config, const std::string& textString, SceneCreateUtilities* createUtilities);

	const GameObjectGroup& GetGameObjects() const;

	virtual void Update() override;



private:
	Config m_config;
	GameObjectGroup m_gameObjects;

	float m_animationTime;
	std::vector<Text*> m_texts;
};