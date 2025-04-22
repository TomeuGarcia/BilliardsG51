#include "CameraShakeSettings.h"

CameraShakeSettings::CameraShakeSettings(const float& shakeAmount01)
	: m_shakeAmount01(shakeAmount01)
{
}

void CameraShakeSettings::SetShakeAmount(const float& shakeAmount01)
{
	m_shakeAmount01 = shakeAmount01;
}

float CameraShakeSettings::GetShakeAmount() const
{
	return m_shakeAmount01;
}
