#include "Renderer.h"


Renderer::Renderer(GameObject* gameObject, const Vector2<float>& worldSize)
    : m_gameObject(gameObject), p_scale(1.0f, 1.0f), r_worldSize(worldSize), p_rotationInDegrees(0),
    p_flip(SDL_FLIP_NONE), m_colorTint(Colors::White)
{
}

Renderer::~Renderer()
{
    SDL_DestroyTexture(r_texture);
}

void Renderer::Update()
{
    UpdateDestination();
}

void Renderer::Render(SDL_Renderer* outputRenderer)
{        
    SDL_Rect destinationRect{ m_destinationRect.ToSDLRect() };
    SDL_RenderCopyEx(outputRenderer, r_texture, GetSourceRect(), &destinationRect, p_rotationInDegrees, NULL, p_flip);
}

void Renderer::SetColorTint(const Color& color)
{
    m_colorTint = color;
    SDL_SetTextureColorMod(r_texture, color.r, color.g, color.b);
    SDL_SetTextureAlphaMod(r_texture, color.a);
}

Color Renderer::GetColorTint() const
{
    return m_colorTint;
}

Rect<int> Renderer::GetDestinationRect() const
{
    return m_destinationRect;
}

const SDL_Rect Renderer::UpdateDestination()
{
    const Vector2<int> position = GameSpacesComputer::GetInstance()->WorldToWindowPosition(
        m_gameObject->GetTransform()->p_worldPosition);
    Vector2<int> scaledSize = GameSpacesComputer::GetInstance()->WorldToWindowVector(
        { r_worldSize.x * p_scale.x, -r_worldSize.y * p_scale.y });

    m_destinationRect = { position, scaledSize };
    return m_destinationRect.ToSDLRect();
}
