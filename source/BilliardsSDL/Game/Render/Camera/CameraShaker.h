#pragma once
#include "Camera2D.h"
#include "ICameraShakePlayer.h"
#include "CameraShakeSettings.h"
#include "../../Systems/GameRandom.h"
#include "../../../Shared/Math/Math.h"


class CameraShaker : public ICameraShakePlayer
{
public:
	struct Config
	{
		float traumaDecreaseSpeed;
		int traumaExponent;

		float maxPositionOffset;
	};

public:
	CameraShaker(const Config& config, Camera2D* shakeCamera);

	void Update(const float& deltaTime, const Camera2D* const defaultCamera);

	CameraShakeSettings* GetSettings();

public:
	virtual void Play(const float& strength01) override;


private:
	CameraShakeSettings m_settings;
	Config m_config;
	Camera2D* m_shakeCamera;

	float m_currentTrauma01;
};