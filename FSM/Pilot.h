#pragma once
#include "AI.h"

enum class PilotLocation
{
	Barraks,
	MechBay,
	Exterior,
	combatZone
};

enum class PilotState
{
	RestingInBarraks,
	PreparingMechForAction,
	MovingToLocation,
	FightingEnemies
};

class Pilot
{
public:
	Pilot() = default;
	void Initialize();
	void Terminate();
	void Update(float deltaTime);
	void ChangeStates(PilotState newState);
	void DebugUI();

	// check miner status
	PilotLocation getLocation() const;
	bool CanFight() const;
	bool OrderReceived() const;
	bool IspilotReady() const;
	bool IsEnemyDestroyed() const;


	//update functions
	void SetLocation(PilotLocation location);
	void RepairMech();
	void fight();
	void HealEnemy();

private:
	AI::StateMachine<Pilot> mStateMachine;
	PilotLocation mLocation;
	int mechHp;
	int enemyHp;
	int distanceToEnemy;
	



};