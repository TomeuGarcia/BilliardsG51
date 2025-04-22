#include "BallCollisionFeedbackManager.h"

BallCollisionFeedbackManager::BallCollisionFeedbackManager(
	const SoundResourceData& ballCollisionWithOtherBallSoundData,
	const SoundResourceData& ballCollisionWithBoardSoundData
)
	: m_activeCollisions(),
	m_ballCollisionWithOtherBallSoundBuffer(GameAudioManager::GetInstance(), ballCollisionWithOtherBallSoundData, 5),
	m_ballCollisionWithBoardSoundBuffer(GameAudioManager::GetInstance(), ballCollisionWithBoardSoundData, 5)
{
}


void BallCollisionFeedbackManager::AddCollisionToHandle(const BallCollision& ballCollision)
{
	for (size_t i = 0; i < m_activeCollisions.size(); ++i)
	{
		if (m_activeCollisions[i].TheSameGameObjectsCollided(ballCollision))
		{
			return;
		}
	}

	m_activeCollisions.emplace_back(ballCollision);
}


void BallCollisionFeedbackManager::Update()
{
	UpdateActiveCollisions();
	ClearActiveCollisions();
}

void BallCollisionFeedbackManager::UpdateActiveCollisions()
{
	for (size_t i = 0; i < m_activeCollisions.size(); ++i)
	{
		PlayCollisionFeedback(m_activeCollisions.at(i));
	}
}

void BallCollisionFeedbackManager::ClearActiveCollisions()
{
	m_activeCollisions.clear();
}

void BallCollisionFeedbackManager::PlayCollisionFeedback(const BallCollision& ballCollision)
{
	float volume = Math::Clamp(ballCollision.GetBallSpeed() / 20.0f, 0.1f, 1.0f);
	volume *= volume;

	if (ballCollision.IsBetweenBalls())
	{
		m_ballCollisionWithOtherBallSoundBuffer.PlayNextWithVolume(volume);
	}
	else
	{
		m_ballCollisionWithBoardSoundBuffer.PlayNextWithVolume(volume);
	}	
}

