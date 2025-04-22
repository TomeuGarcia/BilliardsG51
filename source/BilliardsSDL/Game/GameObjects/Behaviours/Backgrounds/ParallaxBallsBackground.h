#pragma once
#include "../Behaviour.h"
#include "../../../Scenes/Utilities/SceneCreateUtilities.h"



class ParallaxBallsBackground : public Behaviour
{
public:
	struct Config
	{
		int totalInstances;

		Vector2<float> spawnBounds;
		float outOfBoundsY;

		float maxScale;
		float minScale;
		int scaleSteps;

		float maxMoveSpeed;
		float minMoveSpeed;
	};

private:
	struct ParallaxRenderer
	{
		Renderer* renderer;
		float moveSpeed;
	};


public:
	ParallaxBallsBackground(const Config& config, SceneCreateUtilities* createUtilities);


	virtual void Update() override;


private:
	Config m_config;

	std::vector<ParallaxRenderer> m_backgroundRenderers;
	float m_animationTime;
};