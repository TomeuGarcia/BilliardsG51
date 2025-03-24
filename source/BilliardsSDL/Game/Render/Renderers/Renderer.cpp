#include "Renderer.h"


Renderer::Renderer(GameObject* gameObject, const Vector2<int>& size)
    : m_gameObject(gameObject), p_size(size), p_rotationInDegrees(0)
{
}

Renderer::~Renderer()
{
    SDL_DestroyTexture(r_texture);
}

void Renderer::Render(SDL_Renderer* outputRenderer)
{    
    SDL_Rect destinationRect{ ComputeDestination() };
    SDL_RenderCopyEx(outputRenderer, r_texture, &r_sourceRect, &destinationRect, p_rotationInDegrees, NULL, p_flip);
}

const SDL_Rect Renderer::ComputeDestination()
{
    const Vector2<int> position = m_gameObject->GetTransform()->p_position;
    const Vector2<int> halfSize = p_size / 2;

    SDL_Rect destinationRect{};
    destinationRect.x = position.x - halfSize.x;
    destinationRect.y = position.y - halfSize.y;
    destinationRect.w = p_size.x;
    destinationRect.h = p_size.y;


    return destinationRect;
}
