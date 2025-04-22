#pragma once
#include <string>
#include "TextResourceData.h"
#include "../Renderer.h"
#include "../../GameRenderManager.h"


class Text : public Renderer
{
public:
	Text(GameObject* gameObject, const std::string& text, const int pointSize);
	virtual ~Text();

	void Init(const GameRenderManager& renderManager, const TextResourceData& resourceData);
	void Reset(const GameRenderManager& renderManager, const TextResourceData& resourceData, const std::string& text);


protected:
	virtual SDL_Rect* GetSourceRect() override;


private:
	std::string m_text;
	int m_pointSize;
};