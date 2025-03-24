#pragma once
#include "Behaviour.h"
#include "../../Render/Renderers/Image.h"
#include "../../Systems/GameTime.h"

class TestBehaviour : public Behaviour
{
public:
	TestBehaviour(const std::shared_ptr<Image>& image);
	virtual ~TestBehaviour();

public:
	virtual void Update() override;


private:
	std::shared_ptr<Image> m_image;
};