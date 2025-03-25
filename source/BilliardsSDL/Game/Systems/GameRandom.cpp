#include "GameRandom.h"

GameRandom* GameRandom::s_instance = nullptr;

GameRandom::GameRandom(RNGSystem* rngSystem)
	: m_rngSystem(rngSystem)
{
	s_instance = this;
}

GameRandom::~GameRandom()
{
	s_instance = nullptr;
}

GameRandom* GameRandom::GetInstance()
{
	return s_instance;
}

int GameRandom::GetRandomInt(const int minIncluded, const int maxExcluded)
{
	return m_rngSystem->GetRandomInt(minIncluded, maxExcluded);
}

float GameRandom::GetRandomFloat01()
{
	return m_rngSystem->GetRandomFloat01();
}

float GameRandom::GetRandomFloat(const float minIncluded, const float maxIncluded)
{
	return m_rngSystem->GetRandomFloat(minIncluded, maxIncluded);
}

Vector2<float> GameRandom::GetRandomUnitCircle()
{
	Vector2<float> randomVector{ GetRandomFloat(-1.0f, 1.0f) , GetRandomFloat(-1.0f, 1.0f) };
	randomVector.Normalize();
	return randomVector;
}

Vector2<float> GameRandom::GetRandomVectorBetweenBounds(const Vector2<float>& boundsStart, const Vector2<float>& boundsEnd)
{
	return Vector2<float>(GetRandomFloat(boundsStart.x, boundsEnd.x), GetRandomFloat(boundsStart.y, boundsEnd.y));
}

Vector2<float> GameRandom::GetRandomVectorBetweenSignedBounds(const Vector2<float>& bounds)
{
	return GetRandomVectorBetweenBounds(bounds, -bounds);
}

