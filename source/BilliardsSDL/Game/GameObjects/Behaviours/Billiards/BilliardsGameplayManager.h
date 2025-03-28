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

#include "../../../Scenes/SceneManager.h"




class BilliardsGameplayManager : public Behaviour, 
	public IBilliardsGameplayStateEventsManager,
	public IBilliardBoardHoleInteractionsManager
{
public:
	BilliardsGameplayManager();
	~BilliardsGameplayManager();

	void Init(const std::vector<BilliardBall*>& balls, const Vector2<float>& boardCenter,
		BilliardStick* redStick, BilliardStick* blueStick);

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
	void OnWhiteBallEnteredHole();
	void OnBlackBallEnteredHole();
	void OnRedBallEnteredHole(BilliardBall* redBall);
	void OnBlueBallEnteredHole(BilliardBall* blueBall);

	void IncrementPlayerScoreWithThisTurnState();


private:
	std::unordered_map<BilliardsGameplayState::Type, std::shared_ptr<BilliardsGameplayState>> m_gameplayStatesMap;
	BilliardsGameplayState* m_currentState;
	BilliardsGameplayStateBlackboard m_gameplayStatesBlackboard;

	BilliardsPlayer m_playerRed;
	BilliardsPlayer m_playerBlue;


	BilliardBall* m_whiteBall;
	BilliardBall* m_blackBall;

	std::vector<BilliardBall*> m_wellplacedBallsThisTurn;
	std::vector<BilliardBall*> m_missplacedBallsThisTurn;

	bool m_blackBallWellPlaced;
};