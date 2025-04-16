#include "CameraShaker.h"

CameraShaker::CameraShaker(const Config& config, Camera2D* shakeCamera)
	: m_settings(1.0f),
	m_config(config), m_shakeCamera(shakeCamera), m_currentTrauma01(0.0f)
{
}


void CameraShaker::Update(const float& deltaTime, const Camera2D* const defaultCamera)
{
	const float currentShake = Math::Pow(m_currentTrauma01, m_config.traumaExponent) * m_settings.GetShakeAmount();
	m_currentTrauma01 = Math::Clamp01(m_currentTrauma01 - (deltaTime * m_config.traumaDecreaseSpeed));


	const Vector2<float> positionOffset
	{
		m_config.maxPositionOffset * currentShake * GameRandom::GetInstance()->GetRandomFloat(-1.0f, 1.0f),
		m_config.maxPositionOffset * currentShake * GameRandom::GetInstance()->GetRandomFloat(-1.0f, 1.0f)
	};

	m_shakeCamera->SetWorldPosition(defaultCamera->GetWorldPosition() + positionOffset);
}

CameraShakeSettings* CameraShaker::GetSettings()
{
	return &m_settings;
}


void CameraShaker::Play(const float& strength01)
{
	m_currentTrauma01 = Math::Clamp01(m_currentTrauma01 + strength01);
}
