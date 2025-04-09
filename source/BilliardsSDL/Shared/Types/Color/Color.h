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
			r - other.r,
			g - other.g,
			b - other.b,
			a - other.a };
    }
	
	Color operator*(const float& scalar) const
    {
		return Color{
			(int)(r * scalar),
			(int)(g * scalar),
			(int)(b * scalar),
			(int)(a) };
    }

	SDL_Color ToSDLColor() const;

public:
	static Color Lerp(const Color& startingColor, const Color& goalColor, const float& t);
	static Color LerpAlpha(const Color& startingColor, const float& goalAlpha, const float& t);


public:
	int r, g, b, a;	
};


namespace Colors
{
	constexpr inline Color White	{ 255,	255,	255,	255 };
	constexpr inline Color Black	{ 0,	0,		0,		255 };
	constexpr inline Color Red		{ 255,	0,		0,		255 };
	constexpr inline Color Green	{ 0,	255,	0,		255 };
	constexpr inline Color Blue		{ 0,	0,		255,	255 };
	constexpr inline Color Cyan		{ 0,	255,	255,	255 };
	constexpr inline Color Yellow	{ 255,	255,	0,		255 };

	constexpr inline Color SoftRed		{ 220,	30,		70,		255 };
	constexpr inline Color SoftGreen	{ 40,	230,	120,	255 };
	constexpr inline Color SoftBlue		{ 60,	100,	210,	255 };
	constexpr inline Color DarkPurple	{ 90,	30,		90,		255 };

	constexpr inline Color Transparent	{ 0,	0,		0,		0 };
};

