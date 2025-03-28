#include "Color.h"

SDL_Color Color::ToSDLColor() const
{
    return SDL_Color{ (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a };
}

Color Color::Lerp(const Color& a, const Color& b, const float& t)
{
    return a + ((b - a) * t);
}
