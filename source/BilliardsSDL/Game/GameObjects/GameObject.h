#pragma once
#include <memory>
#include "Transform.h"
#include "../Render/Renderers/Renderer.h"


class GameObject
{
public:
	GameObject(const Vector2<int>& position);
	virtual ~GameObject();
	virtual void Update();

public:
	Transform* const GetTransform();

	
	bool HasAttachedRenderer() const;
	Renderer* GetRenderer() const;
	void AttachRenderer(const std::shared_ptr<Renderer>& renderer);
	

private:
	Transform m_transform;
	
	std::shared_ptr<Renderer> m_renderer;
	
};