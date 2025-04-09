#pragma once
#include <algorithm>
#include <set>

#include "../Behaviour.h"
#include "BilliardBall.h"
#include "BilliardStick.h"

#include "../../../Systems/GameInput.h"
#include "../../../Physics/Physics2DManager.h"

#include "States/Init/BilliardsGameplayState_Init.h"
#include "States/PlacingBalls/BilliardsGameplayState_PlacingBalls.h"
#include "States/Thinking/BilliardsGameplayState_PlayerThinking.h"
#include "States/ResolvingBoard/BilliardsGameplayState_ResolvingBoard.h"
#include "States/GameFinish/BilliardsGameplayState_GameFinish.h"

#include "Holes/IBilliardBoardHoleInteractionsManager.h"
#include "BilliardsGameplayFeedbackDisplay.h"
#include "ScoreDisplay/IPlayerScoresDisplay.h"

#include "../../../Scenes/SceneManager.h"




class BilliardsGameplayManager : public Behaviour, 
	public IBilliardsGameplayStateEventsManager,
	public IBilliardBoardHoleInteractionsManager
{
public:
	BilliardsGameplayManager(const BilliardsScore::Configuration& scoreConfiguration);
	~BilliardsGameplayManager();

	void Init(const std::vector<BilliardBall*>& balls, const Vector2<float>& boardCenter,
		BilliardStick* redStick, BilliardStick* blueStick,
		const std::shared_ptr<IPlayerScoresDisplay> scoresDisplay);

	BilliardsGameplayFeedbackDisplay& GetFeedbackDisplay();

	virtual void Update() override;
	virtual void OnDestroy() override;


public:
	virtual bool TryHitWhiteBall(const Vector2<float>& position, const Vector2<float>& direction,
		const float& forceMagnitude) override;
	virtual bool AllBallsStoppedMoving() const override;

	virtual const Vector2<float> FindRandomValidPositionForBall(BilliardBall* ball) const override;

	virtual const std::vector<BilliardBall*>& GetWellplacedBalls() override;
	virtual const std::vector<BilliardBall*>& GetMissplacedBalls() override;
	virtual void ClearWellplacedBalls() override;
	virtual void ClearMissplacedBalls() override;



public:
	void OnBallEnteredHole(BilliardBall* ball, const Vector2<float> holeCenter) override;

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
	std::unordered_map<BilliardsGameplayState::Type, std::shared_ptr<BilliardsGameplayState>> m_gameplayStatesMap;
	BilliardsGameplayState* m_currentState;
	BilliardsGameplayStateBlackboard m_gameplayStatesBlackboard;


	BilliardsGameplayFeedbackDisplay m_feedbackDisplay;
	std::shared_ptr<IPlayerScoresDisplay> m_scoresDisplay;

	BilliardsPlayer m_playerRed;
	BilliardsPlayer m_playerBlue;


	BilliardBall* m_whiteBall;
	BilliardBall* m_blackBall;

	std::vector<BilliardBall*> m_wellplacedBallsThisTurn;
	std::vector<BilliardBall*> m_missplacedBallsThisTurn;

	bool m_blackBallWellPlaced;
};