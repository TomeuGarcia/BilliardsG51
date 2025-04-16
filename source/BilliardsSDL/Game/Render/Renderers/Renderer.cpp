#include "Renderer.h"


Renderer::Renderer(GameObject* gameObject, const Vector2<float>& worldSize)
    : m_gameObject(gameObject), p_scale(1.0f, 1.0f), r_worldSize(worldSize), m_textureState()
{
}

Renderer::~Renderer()
{
    SDL_DestroyTexture(m_textureState.texture);
}

void Renderer::Update(CameraTransformations* cameraTransformations)
{
    m_textureState.sourceRect = GetSourceRect();
    m_textureState.destinationRect = UpdateDestination(cameraTransformations);
}

void Renderer::Render(IOutputRendererVisitor* outputRenderer)
{        
    outputRenderer->DrawTexture(m_textureState);
}

void Renderer::SetColorTint(const Color& color)
{
    m_colorTint = color;
    SDL_SetTextureColorMod(m_textureState.texture, color.r, color.g, color.b);
    SDL_SetTextureAlphaMod(m_textureState.texture, color.a);
}

Color Renderer::GetColorTint() const
{
    return m_colorTint;
}

Rect<int> Renderer::GetDestinationRect() const
{
    return m_destinationRect;
}

bool Renderer::IsActive() const
{
    return m_gameObject->IsActive();
}

GameObject* Renderer::GetGameObject() const
{
    return m_gameObject;
}

Transform* Renderer::GetTransform() const
{
    return m_gameObject->GetTransform();
}

void Renderer::SetRotation(const float& rotationInDegrees)
{
    m_textureState.rotationInDegrees = rotationInDegrees;
}

float Renderer::GetRotation() const
{
    return m_textureState.rotationInDegrees;
}

void Renderer::InitTexture(SDL_Texture* texture)
{
    m_textureState.texture = texture;
}

const SDL_Rect Renderer::UpdateDestination(CameraTransformations* cameraTransformations)
{
    const Vector2<int> position = GameSpacesComputer::GetInstance()->WorldToWindowPosition(
        cameraTransformations->ApplyToWorldPosition(m_gameObject->GetTransform()->p_worldPosition));

    Vector2<int> scaledSize = GameSpacesComputer::GetInstance()->WorldToWindowVector(
        { r_worldSize.x * p_scale.x, -r_worldSize.y * p_scale.y });

    m_destinationRect = { position, scaledSize };
    return m_destinationRect.ToSDLRect();
}
