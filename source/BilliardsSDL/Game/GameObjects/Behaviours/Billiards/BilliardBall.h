#pragma once
#include <memory>
#include "../Behaviour.h"
#include "../../../Render/Renderers/Image/Image.h"
#include "../../../Render/Renderers/Text/Text.h"
#include "../../../Physics/Rigidbodies/Rigidbody2D.h"
#include "../../../Systems/GameRandom.h"



class BilliardBall : public Behaviour
{
public:
	BilliardBall(const std::shared_ptr<Rigidbody2D>& rigidbody);
	~BilliardBall();

public:
	virtual void Start() override;

public:
	void SetPosition(const Vector2<float>& position);


private:
	std::shared_ptr<Rigidbody2D> m_rigidbody;
};