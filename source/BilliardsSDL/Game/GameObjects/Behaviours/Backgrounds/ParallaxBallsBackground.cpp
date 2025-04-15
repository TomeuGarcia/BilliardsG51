#include "ParallaxBallsBackground.h"


ParallaxBallsBackground::ParallaxBallsBackground(const Config& config, SceneCreateUtilities* createUtilities)
	: m_config(config), m_backgroundRenderers(), m_animationTime(0.0f)
{
	m_backgroundRenderers.reserve(config.totalInstances);

	const float scaleGap = config.maxScale - config.minScale;

	for (int i = 0; i < config.totalInstances; ++i)
	{
		const Vector2<float> position = GameRandom::GetInstance()->GetRandomVectorBetweenSignedBounds(config.spawnBounds);
		const ImageResourceData imageData = GameRandom::GetInstance()->GetRandomBool(0.5f)
			? GameAssetResources::GetInstance()->GetImage().blueBallImageData
			: GameAssetResources::GetInstance()->GetImage().redBallImageData;

		const int step = (i * config.scaleSteps) / (config.totalInstances - 1);
		const float stepT = (float)step / config.scaleSteps;

		const float scale = config.minScale + (stepT * scaleGap);
		const Vector2 size = Vector2<float>::One() * scale;

		GameObject* ballGameObject = createUtilities->CreateGameObject(position, std::string("Ball_") + std::to_string(i));
		std::shared_ptr<Image> image = createUtilities->CreateImageComponent(ballGameObject, imageData);
		image->SetColorTint(Colors::White * Math::Lerp(0.1f, 0.6f, (scale - config.minScale) / scaleGap));
		image->p_scale = size;


		const float moveSpeed = Math::Lerp(config.minMoveSpeed, config.maxMoveSpeed, stepT);
		m_backgroundRenderers.emplace_back(image.get(), moveSpeed);
	}
}


void ParallaxBallsBackground::Update()
{	
	const float deltaTime = GameTime::GetInstance()->GetDeltaTime();

	for (auto it = m_backgroundRenderers.begin(); it != m_backgroundRenderers.end(); ++it)
	{
		Vector2<float> newPosition = it->renderer->GetTransform()->p_worldPosition +
			(Vector2<float>::Up() * (it->moveSpeed * deltaTime));

		if (newPosition.y > m_config.outOfBoundsY)
		{
			newPosition.y = -newPosition.y;
			newPosition.x = GameRandom::GetInstance()->GetRandomFloat(-m_config.spawnBounds.x, m_config.spawnBounds.x);
		}

		it->renderer->GetTransform()->p_worldPosition = newPosition;
	}

	m_animationTime += deltaTime;
}
