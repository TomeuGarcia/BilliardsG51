#pragma once
#include "../Behaviour.h"
#include "../MainMenu/MainMenuBilliardsBoardManager.h"


class TitleScreenshotManager : public Behaviour
{
public:
	TitleScreenshotManager(const std::shared_ptr<MainMenuBilliardsBoardManager>& boardManager);

private:
	std::shared_ptr<MainMenuBilliardsBoardManager> m_boardManager;
};