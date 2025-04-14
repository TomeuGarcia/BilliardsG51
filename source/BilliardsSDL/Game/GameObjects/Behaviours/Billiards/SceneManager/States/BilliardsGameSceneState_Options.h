#pragma once
#include "BilliardsGameSceneState.h"
#include "../../../GameOptions/OptionsMenu.h"


class BilliardsGameSceneState_Options : public BilliardsGameSceneState
{
public:
	BilliardsGameSceneState_Options(OptionsMenu* optionsMenu);

	virtual bool Update() override;
	virtual void Exit() override;
protected:
	virtual void DoEnter() override;


private:
	void SetupEnterPaused();


private:
	OptionsMenu* m_optionsMenu;

	bool m_enterPaused;
};