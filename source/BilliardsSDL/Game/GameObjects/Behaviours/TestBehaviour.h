#pragma once
#include "Behaviour.h"
#include "../../Render/Renderers/Image/Image.h"
#include "../../Render/Renderers/Text/Text.h"
#include "../../Systems/GameTime.h"

#include <cmath>


class TestBehaviour : public Behaviour
{
public:
	TestBehaviour(const std::shared_ptr<Image>& image, const std::shared_ptr<Text>& text);
	virtual ~TestBehaviour();

public:
	virtual void Update() override;


private:
	std::shared_ptr<Image> m_image;
	std::shared_ptr<Text> m_text;
};