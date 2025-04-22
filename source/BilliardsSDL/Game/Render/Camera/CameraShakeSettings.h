#pragma once


class CameraShakeSettings
{
public:
	CameraShakeSettings(const float& shakeAmount01);

	void SetShakeAmount(const float& shakeAmount01);
	float GetShakeAmount() const;


private:
	float m_shakeAmount01;
};