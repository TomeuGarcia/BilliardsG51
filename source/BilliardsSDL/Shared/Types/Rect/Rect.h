#pragma once
#include "../Line/Line.h"
#include "SDL.h"


template <typename T>
struct Rect
{
public:
    Rect() 
        : m_centerPosition(), m_size()
    {}

    Rect(Vector2<T> centerPosition, T width, T height) 
        : m_centerPosition(centerPosition), m_size(width, height)
    {
        UpdateCorners();
    }

    Rect(const Vector2<T>& centerPosition, const Vector2<T>& size)
        : m_centerPosition(centerPosition), m_size(size)
    {
        UpdateCorners();
    }

    
    Vector2<T> GetCenterPosition() const
    {
        return m_centerPosition;
    }
    
    Vector2<T> GetSize() const
    {
        return m_size;
    }

    Vector2<T> GetHalfSize() const
    {
        return m_size / 2.0f;
    }

    T GetBottomLeftX() const
    {
        return m_bottomLeftCorner.x;
    }
    T GetBottomLeftY() const
    {
        return m_bottomLeftCorner.y;
    }

    T GetWidth() const
    {
        return m_size.x;
    }
    T GetHeight() const
    {
        return m_size.y;
    }

    void SetCenterPosition(const Vector2<T>& centerPosition)
    {
        m_centerPosition = centerPosition;
        UpdateCorners();
    }
    
    void SetSize(const Vector2<T>& size)
    {
        m_size = size;
        UpdateCorners();
    }



    Line<T> MakeLeftEdgeLine() const
    {
        return Line<T>(m_bottomLeftCorner, MakeTopLeft());
    }
    Line<T> MakeRightEdgeLine() const
    {
        return Line<T>(MakeBottomRight(), m_topRightCorner);
    }
    Line<T> MakeBottomEdgeLine() const
    {
        return Line<T>(m_bottomLeftCorner, MakeBottomRight());
    }
    Line<T> MakeTopEdgeLine() const
    {
        return Line<T>(MakeTopLeft(), m_topRightCorner);
    }


    SDL_Rect ToSDLRect() const
    {
        return SDL_Rect{ m_bottomLeftCorner.x, m_bottomLeftCorner.y, m_size.x, m_size.y };
    }



private:
    void UpdateCorners()
    {
        const T halfWidth = m_size.x / 2;
        const T halfHeight = m_size.y / 2;

        m_bottomLeftCorner.x = m_centerPosition.x - halfWidth;
        m_bottomLeftCorner.y = m_centerPosition.y - halfHeight;

        m_topRightCorner.x = m_centerPosition.x + halfWidth;
        m_topRightCorner.y = m_centerPosition.y + halfHeight;
    }

    Vector2<T> MakeBottomRight() const
    {
        return Vector2<T>(m_topRightCorner.x, m_bottomLeftCorner.y);
    }
    Vector2<T> MakeTopLeft() const
    {
        return Vector2<T>(m_bottomLeftCorner.x, m_topRightCorner.y);
    }



private:
    Vector2<T> m_centerPosition;
    Vector2<T> m_size;

    Vector2<T> m_bottomLeftCorner;
    Vector2<T> m_topRightCorner;
};