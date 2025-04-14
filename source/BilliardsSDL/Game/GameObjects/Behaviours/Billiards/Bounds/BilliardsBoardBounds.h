#pragma once
#include "../../Behaviour.h"
#include "IBilliardsBoardBoundsListener.h"


class BilliardsBoardBounds : public Behaviour
{
public:
	BilliardsBoardBounds(IBilliardsBoardBoundsListener* listener);

	virtual void OnTriggerExit(GameObject* other) override;


private:
	IBilliardsBoardBoundsListener* m_listener;
};