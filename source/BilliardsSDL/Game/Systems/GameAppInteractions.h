#pragma once

class GameAppInteractions
{
public:
	GameAppInteractions();
	~GameAppInteractions();

	static GameAppInteractions* GetInstance();


	void Quit();
	bool WantsToQuit() const;


private:
	bool m_quit;

private:
	static GameAppInteractions* s_instance;
};