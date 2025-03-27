#pragma once
#include <cstdint>
#include <SDL.h>

struct Color
{
public:
	Color operator+(const Color& other) const
    {
        return Color{ 
			r + other.r, 
			g + other.g, 
			b + other.b, 
			a + other.a };
    }

	Color operator-(const Color& other) const
    {
		return Color{
			r + other.r,
			g + other.g,
			b + other.b,
			a + other.a };
    }
	
	Color operator*(const float& scalar) const
    {
		return Color{
			(uint32_t)(r * scalar),
			(uint32_t)(g * scalar),
			(uint32_t)(b * scalar),
			(uint32_t)(a * scalar) };
    }

	SDL_Color ToSDLColor() const;

public:
	static Color Lerp(const Color& a, const Color& b, const float& t);


public:
	uint32_t r, g, b, a;	
};


namespace Colors
{
	constexpr const Color White	{ 255,	255,	255,	255 };
	constexpr const Color Black	{ 0,	0,		0,		255 };
	constexpr const Color Red	{ 255,	0,		0,		255 };
	constexpr const Color Green	{ 0,	255,	0,		255 };
	constexpr const Color Blue	{ 0,	0,		255,	255 };
	constexpr const Color Cyan	{ 0,	255,	255,	255 };

	constexpr const Color SoftRed	{ 230,	40,		60,		255 };
	constexpr const Color SoftGreen	{ 40,	230,	120,	255 };
	constexpr const Color SoftBlue	{ 60,	80,		210,	255 };
};

