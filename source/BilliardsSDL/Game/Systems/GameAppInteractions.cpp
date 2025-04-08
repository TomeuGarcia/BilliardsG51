#include "GameAppInteractions.h"


GameAppInteractions* GameAppInteractions::s_instance = nullptr;

GameAppInteractions::GameAppInteractions()
	: m_quit(false)
{
	s_instance = this;
}

GameAppInteractions::~GameAppInteractions()
{
	s_instance = nullptr;
}



GameAppInteractions* GameAppInteractions::GetInstance()
{
	return s_instance;
}



void GameAppInteractions::Quit()
{
	m_quit = true;
}

bool GameAppInteractions::WantsToQuit() const
{
	return m_quit;
}
