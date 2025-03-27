#pragma once
#include "../Behaviour.h"
#include "BilliardBall.h"
#include "BilliardStick.h"

#include "../../../Systems/GameInput.h"

#include "States/Thinking/PlayerThinkingFSM.h"


class BilliardsGameplayManager : public Behaviour
{
public:
	BilliardsGameplayManager();
	~BilliardsGameplayManager();

	void Init(BilliardStick* stick);

	virtual void Update() override;


private:
	BilliardStick* m_stick;

	Vector2<float> m_pinPosition;
	bool m_pinned;


	PlayerThinkingFSM m_playerthinkingFsm;
};