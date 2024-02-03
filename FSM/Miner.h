#pragma once
#include "AI.h"

enum class Location
{
	Home,
	Mine,
	Saloon,
	Bank
};

enum class MinerState
{
	GoHomeAndSleeptUntillRested,
	EnterMineAndDigForNugget,
	QuenchThirst,
	VisitBankAndDepositGold
};

class Miner
{
public:
	Miner()=default;
	void Initialize();
	void Terminate();
	void Update(float deltaTime);
	void ChangeStates(MinerState newState);
	void DebugUI();

	// check miner status
	Location getLocation() const;
	bool IsThirsty() const;
	bool IsPoketFull() const;
	bool IsWealthy() const;
	bool IsRested() const;

	//update functions

	void SetLocation(Location location);
	void IncreaseFatigue();
	void IncreaseGoldCarried(int amount);
	void AddGoldToBank();

	void ResetFatigue();
	void ResetThirst();

private:
	AI::StateMachine<Miner> mStateMachine;
	Location mLocation;
	int mGoldCarried;
	int mMoneyInBank;
	int mThirst;
	int mFatigue;

};