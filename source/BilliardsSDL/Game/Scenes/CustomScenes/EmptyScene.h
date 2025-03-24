#pragma once
#include "../Scene.h"
#include "../../GameObjects/Behaviours/TestBehaviour.h"

class EmptyScene : public Scene
{
public:
	EmptyScene(const Color& backgroundColor);
	virtual ~EmptyScene();

protected:
	virtual void CreateGameObjects() override;
	virtual void Start() override;


private:
	Color m_backgroundColor;
};