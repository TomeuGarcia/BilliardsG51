#pragma once
#include <utility>
#include <iostream>
#include "GameSystems.h"

class BilliardsGame
{
public:
	BilliardsGame();
	~BilliardsGame();
	void Init(const GameSystems& systems);
	void Cleanup();

	void Update();
	void Render() const;



public:
	bool p_quitApplication;
private:
	GameSystems m_systems;

};