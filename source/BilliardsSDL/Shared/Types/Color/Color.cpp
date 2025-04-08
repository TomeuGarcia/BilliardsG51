#include "Color.h"

SDL_Color Color::ToSDLColor() const
{
    return SDL_Color{ (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a };
}

Color Color::Lerp(const Color& startingColor, const Color& goalColor, const float& t)
{
    Color result = startingColor + ((goalColor - startingColor) * t);
    result.a = startingColor.a + ((goalColor.a - startingColor.a) * t);

    return result;
}

Color Color::LerpAlpha(const Color& startingColor, const float& goalAlpha, const float& t)
{
    Color result = startingColor;
    result.a = startingColor.a + ((goalAlpha - startingColor.a) * t);

    return result;
}
