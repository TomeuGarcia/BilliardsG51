#pragma once
#include "../../Application/Systems/Random/RNGSystem.h"
#include "../../Shared/Types/Vector2/Vector2.h"


class GameRandom
{
public:
	GameRandom(RNGSystem* rngSystem);
	~GameRandom();

	static GameRandom* GetInstance();

public:
	int GetRandomInt(const int minIncluded, const int maxExcluded);
	float GetRandomFloat01();
	float GetRandomFloat(const float minIncluded, const float maxIncluded);
	bool GetRandomBool(const float trueChance01);
	Vector2<float> GetRandomUnitCircle();
	Vector2<float> GetRandomVectorBetweenBounds(const Vector2<float>& boundsStart, const Vector2<float>& boundsEnd);
	Vector2<float> GetRandomVectorBetweenSignedBounds(const Vector2<float>& bounds);


private:
	RNGSystem* m_rngSystem;

private:
	static GameRandom* s_instance;

};