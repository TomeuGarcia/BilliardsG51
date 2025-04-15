#pragma once
#include <algorithm>
#include <set>

#include "../Behaviour.h"
#include "BilliardBall.h"
#include "BilliardStick.h"

#include "../../../Systems/GameInput.h"
#include "../../../Physics/Physics2DManager.h"
#include "../../../Physics/Helpers/GamePhysicsUtilities.h"

#include "States/BilliardsGameplayFSM.h"

#include "Holes/IBilliardBoardHoleInteractionsManager.h"
#include "Bounds/IBilliardsBoardBoundsListener.h"
#include "BilliardsGameplayFeedbackDisplay.h"
#include "ScoreDisplay/IPlayerScoresDisplay.h"

#include "../Ranking/RankingManager.h"

#include "../../../Scenes/SceneManager.h"




class BilliardsGameplayManager : public Behaviour, 
	public IBilliardsGameplayStateEventsManager,
	public IBilliardBoardHoleInteractionsManager,
	public IBilliardsBoardBoundsListener
{
public:
	BilliardsGameplayManager(const BilliardsScore::Configuration& scoreConfiguration);
	~BilliardsGameplayManager();

	void Init(const std::vector<BilliardBall*>& balls, const Vector2<float>& boardCenter,
		BilliardStick* redStick, BilliardStick* blueStick,
		const std::shared_ptr<BilliardsGameplayFeedbackDisplay>& feedbackDisplay,
		const std::shared_ptr<IPlayerScoresDisplay>& scoresDisplay);


	virtual void OnDestroy() override;


	BilliardsGameplayStateBlackboard* GetBlackboard();


public:
	virtual bool CanHitWhiteBall(const Vector2<float>& position) override;
	virtual void HitWhiteBall(const Vector2<float>& direction, const float& forceMagnitude) override;
	virtual bool AllBallsStoppedMoving() const override;

	virtual void PositionBallsRandomly() const override;
	virtual const Vector2<float> FindRandomValidPositionForBall(BilliardBall* ball) const override;

	virtual const std::vector<BilliardBall*>& GetWellplacedBalls() override;
	virtual const std::vector<BilliardBall*>& GetMissplacedBalls() override;
	virtual void ClearWellplacedBalls() override;
	virtual void ClearMissplacedBalls() override;

	virtual void OnPlayerStartsPlaying() override;
	virtual void OnGameFinishStart() override;

	virtual void AskWinnerNameAndAddToRanking(BilliardsPlayer* winnerPlayer) override;


public:
	virtual void OnBallEnteredHole(BilliardBall* ball, const Vector2<float>& holeCenter) override;


public:
	virtual void OnBallExitsBoardBounds(BilliardBall* ball) override;


private:
	void OnAnyBallEnteredHole(BilliardBall* ball, const Vector2<float>& holeCenter);
	void OnWhiteBallEnteredHole(const Vector2<float>& holeCenter);
	void OnBlackBallEnteredHole(const Vector2<float>& holeCenter);
	void OnRedBallEnteredHole(BilliardBall* redBall, const Vector2<float>& holeCenter);
	void OnBlueBallEnteredHole(BilliardBall* blueBall, const Vector2<float>& holeCenter);
	void OnPlayerBallEnteredHole(BilliardBall* ball, const Vector2<float>& holeCenter, BilliardsPlayer* ballOwnerPlayer);

	void IncrementPlayerScoreWithThisTurnState(const Vector2<float>& holeCenter);

	void OnScoreChanged();


private:
	BilliardsGameplayStateBlackboard m_gameplayStatesBlackboard;

	std::shared_ptr<BilliardsGameplayFeedbackDisplay> m_feedbackDisplay;
	std::shared_ptr<IPlayerScoresDisplay> m_scoresDisplay;

	BilliardsPlayer m_playerRed;
	BilliardsPlayer m_playerBlue;


	BilliardBall* m_whiteBall;
	BilliardBall* m_blackBall;

	std::vector<BilliardBall*> m_wellplacedBallsThisTurn;
	std::vector<BilliardBall*> m_missplacedBallsThisTurn;

	bool m_blackBallWellPlaced;
};