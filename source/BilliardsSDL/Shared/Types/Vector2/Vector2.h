#pragma once
#ifndef SDLPROJECT_VECTOR2D_H
#define SDLPROJECT_VECTOR2D_H
#include <cmath>


/// <summary>
/// Tomeu: I took this class from an older project and adapr
/// </summary>
/// <typeparam name="T"></typeparam>

template <typename T>
class Vector2
{
public:
    Vector2() : x(0), y(0) 
    {}
    Vector2(T X, T Y) : x(X), y(Y) 
    {}

    [[nodiscard]] T Length() const 
    { 
        return sqrt(x * x + y * y); 
    };

    Vector2 operator+(const Vector2& v2) const 
    { 
        return { x + v2.x, y + v2.y }; 
    }
    friend Vector2& operator+=(Vector2& v1, const Vector2& v2)
    {
        v1.x += v2.x;
        v1.y += v2.y;
        return v1;
    }

    Vector2 operator-() const 
    { 
        return { -x , -y }; 
    }
    Vector2 operator-(const Vector2& v2) const 
    { 
        return { x - v2.x, y - v2.y }; 
    }
    friend Vector2& operator-=(Vector2& v1, const Vector2& v2)
    {
        v1.x -= v2.x;
        v1.y -= v2.y;
        return v1;
    }

    Vector2 operator*(T scalar) const 
    { 
        return Vector2{ x * scalar, y * scalar };
    }
    friend Vector2 operator*(const Vector2& v1, const Vector2& v2)
    {
        return Vector2{ v1.x * v2.x, v1.y * v2.y };
    }
    friend Vector2& operator*=(Vector2& v1, const Vector2& v2)
    {
        v1.x *= v2.x;
        v1.y *= v2.y;
        return v1;
    }
    Vector2& operator*=(T scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2 operator/(T scalar) const 
    { 
        return Vector2{ x / scalar, y / scalar };
    }
    Vector2& operator/=(T scalar)
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    Vector2& operator%=(T scalar)
    {
        x %= scalar;
        y %= scalar;
        return *this;
    }



    void Normalize()
    {
        T length = Length();
        if (length > 0)
        {
            (*this) /= length;
        }
    }

    Vector2 Normalized() const
    {
        T length = Length();
        if (length > 0)
        {
            return *this / length;
        }
        return *this;
    }

    static T Distance(const Vector2& v1, const Vector2& v2)
    {
        return (v2 - v1).Length();
    }

    static T Dot(const Vector2& v1, const Vector2& v2)
    {
        return (v1.x * v2.x) + (v1.y * v2.y);
    }
    
    static T Cross(const Vector2& v1, const Vector2& v2)
    {
        return (v1.x * v2.y) - (v1.y * v2.x);
    }

    static Vector2 Lerp(const Vector2& v1, const Vector2& v2, const float t)
    {
        return v1 + (v2 - v1) * t;
    }

    static inline Vector2 Zero() 
    {
        return { 0, 0 };
    }
    static inline Vector2 One()
    {
        return { 1, 1 };
    }
    static inline Vector2 Right()
    {
        return { 1, 0 };
    }
    static inline Vector2 Left()
    {
        return { -1, 0 };
    }
    static inline Vector2 Up()
    {
        return { 0, 1 };
    }
    static inline Vector2 Down()
    {
        return { 0, -1 };
    }


public:
    T x;
    T y;
};


#endif //SDLPROJECT_VECTOR2D_H
