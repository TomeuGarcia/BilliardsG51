#include "MenuIncDecButton.h"

#include "../../Prefabs/CustomPrefabUtilities.h"




MenuIncDecButton::MenuIncDecButton(SceneCreateUtilities* sceneCreateUtilities, const Config& config,
    const std::string& name, const int& startingValue, GameObject* gameObject)
    : 
    m_gameObjects(5),
    m_incrementButton(nullptr), m_decrementButton(nullptr), m_nameText(nullptr), m_valueTexts(),
    m_textColor(config.textColor),
    m_numberOfSteps(config.numberOfSteps + 1),
    m_currentValueIndex(0),
    m_minValue(config.minValue),
    m_maxValue(config.maxValue),
    m_valueUpdateCallback(),
    m_incSound(GameAudioManager::GetInstance()->CreateSFXSound(*config.incSoundData)),
    m_decSound(GameAudioManager::GetInstance()->CreateSFXSound(*config.decSoundData))
{
    m_currentValueIndex = ((float)(startingValue - m_minValue) / (m_maxValue - m_minValue)) * config.numberOfSteps;

    const Vector2<float> centerPosition = gameObject->GetTransform()->p_worldPosition;

    GameObject* nameGameObject = sceneCreateUtilities->CreateGameObject(centerPosition + Vector2<float>(-2.0f, 0.0f), "Name_" + name);
    sceneCreateUtilities->CreateTextComponent(nameGameObject, *config.textData, name, config.nameTextPointSize);

    GameObject* incGameObject = sceneCreateUtilities->CreateGameObject(centerPosition + Vector2<float>(2.0f, 0.0f), "Inc");
    std::shared_ptr<Text> incText = sceneCreateUtilities->CreateTextComponent(incGameObject, *config.textData, "+", config.buttonsPointSize);
    m_incrementButton = sceneCreateUtilities->CreateButton(incText, config.incColorBlock).get();
    m_incrementButton->p_onSelectedCallback = std::bind(&MenuIncDecButton::IncrementValue, this);
    
    GameObject* decGameObject = sceneCreateUtilities->CreateGameObject(centerPosition + Vector2<float>(1.5f, 0.0f), "Dec");
    std::shared_ptr<Text> decText = sceneCreateUtilities->CreateTextComponent(decGameObject, *config.textData, "-", config.buttonsPointSize);
    m_decrementButton = sceneCreateUtilities->CreateButton(decText, config.decColorBlock).get();
    m_decrementButton->p_onSelectedCallback = std::bind(&MenuIncDecButton::DecrementValue, this);

    GameObject* valueTextsGameObject = sceneCreateUtilities->CreateGameObject(centerPosition + Vector2<float>(0.4f, 0.0f), "ValueTexts");
    m_valueTexts.reserve(m_numberOfSteps);
    for (int i = 0; i < m_numberOfSteps; ++i)
    {
        const int value = ComputeValue(i);
        std::shared_ptr<Text> valueText = 
            sceneCreateUtilities->CreateTextComponent(valueTextsGameObject, *config.textData, std::to_string(value), config.valueTextsPointSize);

        m_valueTexts.emplace_back(valueText.get());
    }
    UpdateValueText();


    m_gameObjects.Add(gameObject);
    m_gameObjects.Add(nameGameObject);
    m_gameObjects.Add(incGameObject);
    m_gameObjects.Add(decGameObject);
    m_gameObjects.Add(valueTextsGameObject);
}

void MenuIncDecButton::SetValueUpdateCallback(const std::function<void(int)>& valueUpdateCallback)
{
    m_valueUpdateCallback = valueUpdateCallback;
}


const GameObjectGroup& MenuIncDecButton::GetGameObjects()
{
    return m_gameObjects;
}


const int MenuIncDecButton::GetValueMaxIndex() const
{
    return m_valueTexts.size() - 1;
}

void MenuIncDecButton::IncrementValue()
{
    if (m_currentValueIndex == GetValueMaxIndex())
    {
        return;
    }

    m_incSound->Play();
    ++m_currentValueIndex;

    UpdateValue();
}

void MenuIncDecButton::DecrementValue()
{
    if (m_currentValueIndex == 0)
    {
        return;
    }

    m_decSound->Play();
    --m_currentValueIndex;

    UpdateValue();
}

void MenuIncDecButton::UpdateValue()
{
    UpdateValueText();
    m_valueUpdateCallback(ComputeValue(m_currentValueIndex));
}


void MenuIncDecButton::UpdateValueText()
{
    for (size_t i = 0; i < m_valueTexts.size(); ++i)
    {
        const Color visibilityColor = i == m_currentValueIndex
            ? m_textColor
            : m_textColor.WithAlpha(0);

        m_valueTexts[i]->SetColorTint(visibilityColor);
    }
}

int MenuIncDecButton::ComputeValue(const int& index) const
{
    const float t = (float)index / (m_numberOfSteps-1);
    return m_minValue + ((m_maxValue - m_minValue) * t);
}
