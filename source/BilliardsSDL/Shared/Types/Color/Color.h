#pragma once
#include <cstdint>

struct Color
{
public:
	uint8_t r, g, b, a;	
};


namespace Colors
{
	constexpr const Color White	{ 255,	255,	255,	255 };
	constexpr const Color Black	{ 0,	0,		0,		255 };
	constexpr const Color Red	{ 255,	0,		0,		255 };
	constexpr const Color Green	{ 0,	255,	0,		255 };
	constexpr const Color Blue	{ 0,	0,		255,	255 };

	constexpr const Color SoftRed	{ 230,	40,		60,		255 };
	constexpr const Color SoftGreen	{ 40,	230,	120,	255 };
	constexpr const Color SoftBlue	{ 60,	80,		210,	255 };
};

