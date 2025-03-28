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
	bool TryHitWhiteBall(const Vector2<float>& position, const Vector2<float>& direction,
		const float& forceMagnitude) override;
	virtual bool AllBallsStoppedMoving() const override;

public:
	void OnBallEnteredHole(BilliardBall* ball, const Vector2<float> holeCenter) override;

private:
	void OnAnyBallEnteredHole(BilliardBall* ball);
	void OnWhiteBallEnteredHole();
	void OnBlackBallEnteredHole();
	void OnRedBallEnteredHole(BilliardBall* redBall);
	void OnBlueBallEnteredHole(BilliardBall* blueBall);


	const Vector2<float> FindRandomValidPositionForBall(BilliardBall* ball) const;


private:
	std::unordered_map<BilliardsGameplayState::Type, std::shared_ptr<BilliardsGameplayState>> m_gameplayStatesMap;
	BilliardsGameplayState* m_currentState;
	BilliardsGameplayStateBlackboard m_gameplayStatesBlackboard;

	BilliardsPlayer m_playerRed;
	BilliardsPlayer m_playerBlue;


	BilliardBall* m_whiteBall;
	BilliardBall* m_blackBall;

	std::set<BilliardBall*> m_remainingRedBalls;
	std::set<BilliardBall*> m_remainingBlueBalls;
};