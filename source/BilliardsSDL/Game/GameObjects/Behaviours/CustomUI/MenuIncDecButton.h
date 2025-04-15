#pragma once
#include <functional>
#include <vector>

#include "../Behaviour.h"
#include "../../GameObjectGroup.h"
#include "../../../Render/Renderers/Text/Text.h"
#include "../../../Audio/GameAudioManager.h"
#include "../../../UI/Selectables/Button/UIButton.h"
#include "../../../Systems/GameAssetResourceTypes.h"



class SceneCreateUtilities;

class MenuIncDecButton : public Behaviour
{
public:
	struct Config
	{
	public:
		int minValue;
		int maxValue;
		int numberOfSteps;

		int nameTextPointSize;
		int valueTextsPointSize;
		int buttonsPointSize;

		ColorBlock incColorBlock;
		ColorBlock decColorBlock;

		const SoundResourceData* incSoundData;
		const SoundResourceData* decSoundData;

		const TextResourceData* textData;
		Color textColor;
	};


public:
	MenuIncDecButton(SceneCreateUtilities* sceneCreateUtilities, const Config& config, 
		const std::string& name, const int& startingValue, GameObject* gameObject);

	void Init(const int& startingValue);

	void SetValueUpdateCallback(const std::function<void(int)>& valueUpdateCallback);

	const GameObjectGroup& GetGameObjects();


private:
	const int GetValueMaxIndex() const;

	void IncrementValue();
	void DecrementValue();
	void UpdateValue();

	void UpdateValueText();
	int ComputeValue(const int& index) const;




private:
	GameObjectGroup m_gameObjects;

	UIButton* m_incrementButton;
	UIButton* m_decrementButton;

	Text* m_nameText;

	std::vector<Text*> m_valueTexts;

	Color m_textColor;


	int m_numberOfSteps;
	int m_currentValueIndex;
	int m_minValue;
	int m_maxValue;

	std::function<void(int)> m_valueUpdateCallback;

	std::shared_ptr<SFXSound> m_incSound;
	std::shared_ptr<SFXSound> m_decSound;
};