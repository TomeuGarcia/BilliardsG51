#include "RNGSystem.h"

RNGSystem::RNGSystem()
	: m_seed(0)
{
}

RNGSystem::~RNGSystem()
{
}

void RNGSystem::Init()
{
	m_seed = time(NULL);
	srand(m_seed);
}

int RNGSystem::GetRandomInt(const int minIncluded, const int maxExcluded)
{
	return minIncluded + (rand() % (maxExcluded - minIncluded));
}

float RNGSystem::GetRandomFloat01()
{
	return (float)(rand()) / (float)(RAND_MAX);
}

float RNGSystem::GetRandomFloat(const float minIncluded, const float maxIncluded)
{
	return minIncluded + (GetRandomFloat01() * (maxIncluded - minIncluded));
}
