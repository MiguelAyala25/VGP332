#pragma once


#include <AI.h>
#include "Pilot.h"

class RestingInBarraksState : public AI::State<Pilot>
{
public:
	void Enter(Pilot& agent) override;
	void Update(Pilot& agent, float deltaTime) override;
	void Exit(Pilot& agent) override;
	void DebugUI() override;
};

class PreparingMechForActionState : public AI::State<Pilot>
{
public:
	void Enter(Pilot& agent) override;
	void Update(Pilot& agent, float deltaTime) override;
	void Exit(Pilot& agent) override;
	void DebugUI() override;
};

class MovingToLocation : public AI::State<Pilot>
{
public:
	void Enter(Pilot& agent) override;
	void Update(Pilot& agent, float deltaTime) override;
	void Exit(Pilot& agent) override;
	void DebugUI() override;
};

class FightingEnemies : public AI::State<Pilot>
{
public:
	void Enter(Pilot& agent) override;
	void Update(Pilot& agent, float deltaTime) override;
	void Exit(Pilot& agent) override;
	void DebugUI() override;
};
