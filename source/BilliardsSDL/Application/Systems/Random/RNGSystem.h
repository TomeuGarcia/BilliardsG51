#pragma once
#include <time.h>
#include <iostream>

class RNGSystem
{
public:
	RNGSystem();
	~RNGSystem();

	void Init();

	int GetRandomInt(const int minIncluded, const int maxExcluded);
	float GetRandomFloat01();
	float GetRandomFloat(const float minIncluded, const float maxIncluded);


private:
	int m_seed;
};