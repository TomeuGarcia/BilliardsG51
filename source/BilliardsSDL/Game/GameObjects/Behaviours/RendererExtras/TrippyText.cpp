#include "TrippyText.h"


TrippyText::TrippyText(GameObject* gameObject, const Config& config, const std::string& textString, SceneCreateUtilities* createUtilities)
	: 
	m_config(config),
	m_animationTime(0.0f),
	m_gameObjects(1),
	m_texts()
{

	m_texts.reserve(m_config.numberOfTexts);

	for (size_t i = 0; i < m_config.numberOfTexts; ++i)
	{
		Text* text = createUtilities->CreateTextComponent(gameObject, *m_config.textFontData, textString, m_config.textPointSize).get();
		
		Color color;
		if (i == m_config.numberOfTexts - 1)
		{
			color = m_config.frontmostColor;
		}
		else
		{
			const float colorT = (float)i / (m_config.numberOfTexts - 1.0f);
			color = Color::Lerp(m_config.backColor1, m_config.frontColor, colorT);
		}
		
		text->SetColorTint(color);

		m_texts.emplace_back(text);
	}

	m_gameObjects.Add(gameObject);
}

const GameObjectGroup& TrippyText::GetGameObjects() const
{
	return m_gameObjects;
}



void TrippyText::Update()
{
	const float backColorT = Math::Sin01(m_animationTime);
	const Color backColor = Color::Lerp(m_config.backColor1, m_config.backColor2, backColorT);


	for (size_t i = 0; i < m_texts.size(); ++i)
	{
		Text* text = m_texts[i];

		const float animationTime = m_animationTime + (i * m_config.textsTimeOffset);
		const float rotationAngle = Math::Sin(animationTime * m_config.rotationSpeed) * m_config.maxRotation;

		text->SetRotation(rotationAngle);


		if (i < m_config.numberOfTexts - 1)
		{
			float colorT = (float)i / (m_config.numberOfTexts - 1.0f);
			colorT *= colorT;

			Color color = Color::Lerp(backColor, m_config.frontColor, colorT);
			text->SetColorTint(color);
		}

	}


	m_animationTime += GameTime::GetInstance()->GetDeltaTime();
}
