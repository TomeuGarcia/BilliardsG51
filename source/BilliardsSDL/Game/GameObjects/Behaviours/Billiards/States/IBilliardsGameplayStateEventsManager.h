#pragma once
#include "../../../../../Shared/Types/Vector2/Vector2.h"
#include "../BilliardBall.h"
#include "../Player/BilliardsPlayer.h"


class IBilliardsGameplayStateEventsManager
{
public:
	virtual bool TryHitWhiteBall(const Vector2<float>& position, const Vector2<float>& direction, 
		const float& forceMagnitude) = 0;

	virtual bool AllBallsStoppedMoving() const = 0;


	virtual const Vector2<float> FindRandomValidPositionForBall(BilliardBall* ball) const = 0;


	virtual const std::vector<BilliardBall*>& GetWellplacedBalls() = 0;
	virtual const std::vector<BilliardBall*>& GetMissplacedBalls() = 0;
	virtual void ClearWellplacedBalls() = 0;
	virtual void ClearMissplacedBalls() = 0;


	virtual void OnPlayerStartsPlaying() = 0;
	virtual void OnGameFinishStart() = 0;


	virtual void AskWinnerNameAndAddToRanking(BilliardsPlayer* winnerPlayer) = 0;
};