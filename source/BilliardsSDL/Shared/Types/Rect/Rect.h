#pragma once
#include "../Line/Line.h"

template <typename T>
struct Rect
{
public:
    Rect() : x(0), y(0)
    {
    }
    Rect(T X, T Y) : x(X), y(Y)
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

public:
    T x, y, width, height;
};