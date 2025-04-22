#pragma once
#include <vector>
#include "../../Behaviour.h"

#include "IBallCollisionFeedbackManager.h"

#include "../../../../Audio/SoundResourceData.h"
#include "../../../../Audio/GameAudioManager.h"
#include "../../../../Audio/SFXSoundBuffer.h"


class BallCollisionFeedbackManager : public Behaviour, public IBallCollisionFeedbackManager
{
public:
	BallCollisionFeedbackManager(
		const SoundResourceData& ballCollisionWithOtherBallSoundData,
		const SoundResourceData& ballCollisionWithBoardSoundData
	);

	virtual void AddCollisionToHandle(const BallCollision& ballCollision) override;
	
	virtual void Update() override;


private:
	void UpdateActiveCollisions();
	void ClearActiveCollisions();

	void PlayCollisionFeedback(const BallCollision& ballCollision);


private:
	std::vector<BallCollision> m_activeCollisions;

	SFXSoundBuffer m_ballCollisionWithOtherBallSoundBuffer;
	SFXSoundBuffer m_ballCollisionWithBoardSoundBuffer;

};