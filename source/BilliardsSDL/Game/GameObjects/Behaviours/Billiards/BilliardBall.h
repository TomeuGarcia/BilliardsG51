#pragma once
#include <memory>
#include "../Behaviour.h"
#include "../../../Render/Renderers/Image/Image.h"
#include "../../../Render/Renderers/Text/Text.h"
#include "../../../Physics/Rigidbodies/Rigidbody2D.h"
#include "../../../Systems/GameRandom.h"
#include "../../../Systems/GameSpacesComputer.h"
#include "../../../Render/GameRenderManager.h"



class BilliardBall : public Behaviour
{
public:
	BilliardBall(const std::shared_ptr<Rigidbody2D>& rigidbody);
	~BilliardBall();

public:
	virtual void Start() override;
	virtual void Update() override;

public:
	void SetPosition(const Vector2<float>& position);
	Transform* GetTransform() const;


	void SetIgnoringPhysics();
	void SetUsingPhysics();


private:
	std::shared_ptr<Rigidbody2D> m_rigidbody;
	Vector2<float> m_startPosition;
};