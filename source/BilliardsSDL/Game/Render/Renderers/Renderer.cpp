#include "Renderer.h"


Renderer::Renderer(GameObject* gameObject, const Vector2<int>& size)
    : m_gameObject(gameObject), p_scale(1.0f, 1.0f), r_size(size), p_rotationInDegrees(0),
    p_flip(SDL_FLIP_NONE), m_colorTint(Colors::White)
{
}

Renderer::~Renderer()
{
    SDL_DestroyTexture(r_texture);
}

void Renderer::Render(SDL_Renderer* outputRenderer)
{    
    SDL_Rect destinationRect{ ComputeDestination() };
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

const SDL_Rect Renderer::ComputeDestination()
{
    const Vector2<int> position = m_gameObject->GetTransform()->p_position;
    const Vector2<int> scaledSize{ (int)(r_size.x * p_scale.x), (int)(r_size.y * p_scale.y) };
    const Vector2<int> halfScaledSize = scaledSize / 2;

    SDL_Rect destinationRect{};
    destinationRect.x = position.x - halfScaledSize.x;
    destinationRect.y = position.y - halfScaledSize.y;
    destinationRect.w = scaledSize.x;
    destinationRect.h = scaledSize.y;

    return destinationRect;
}
