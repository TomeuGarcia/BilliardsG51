#pragma once
#include "../Line/Line.h"
#include "SDL.h"


template <typename T>
struct Rect
{
public:
    Rect() : x(0), y(0)
    {
    }
    Rect(T X, T Y, T Width, T Height) : x(X), y(Y), width(Width), height(Height)
    {
    }

    Rect(const Vector2<T>& position, const Vector2<T>& size) : x(position.x), y(position.y), width(size.x), height(size.y)
    {
    }

    Line MakeLeftEdgeLine() const
    {
        return Line(Vector2<float>(x, y), Vector2<float>(x, y + height));
    }
    Line MakeRightEdgeLine() const
    {
        return Line(Vector2<float>(x + width, y), Vector2<float>(x + width, y + height));
    }
    Line MakeBottomEdgeLine() const
    {
        return Line(Vector2<float>(x, y), Vector2<float>(x + width, y));
    }
    Line MakeTopEdgeLine() const
    {
        return Line(Vector2<float>(x, y + height), Vector2<float>(x + width, y + height));
    }

    SDL_Rect ToSDLRect() const
    {
        return SDL_Rect{ x, y, width, height };
    }


public:
    T x, y, width, height;
};