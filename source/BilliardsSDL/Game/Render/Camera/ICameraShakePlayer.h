#pragma once


class ICameraShakePlayer
{
public:
	virtual void Play(const float& strength01) = 0;
};